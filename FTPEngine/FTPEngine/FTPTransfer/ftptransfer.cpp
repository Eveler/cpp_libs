#include "ftptransfer.h"
#include "amslogger.h"

FTPTransfer::FTPTransfer(QObject *parent) :
  QObject(parent),
  m__Server(new QTcpServer),
  m__Client(NULL),
  m__State(FTPTransfer::State_None),
  m__Buffer(NULL),
  m__BytesDone(0),
  passive(true),
  transfer(NULL),
  loop(new QEventLoop(this))
{
  connect( m__Server, SIGNAL(newConnection()), SLOT(incomingConnection()) );
}

FTPTransfer::~FTPTransfer()
{
  delete m__Server;
  m__Server = NULL;
  m__Client = NULL;
  loop->deleteLater();
}

bool FTPTransfer::listen( QHostAddress localAddress )
{
  return m__Server->listen( localAddress );
}

QHostAddress FTPTransfer::address() const
{
  return m__Server->serverAddress();
}

quint16 FTPTransfer::port() const
{
  return m__Server->serverPort();
}

void FTPTransfer::setBuffer( QIODevice *buffer )
{
    m__Buffer = buffer;
}

bool FTPTransfer::startUploading()
{
    return uploadNext();
}

void FTPTransfer::setTransferMode(bool isPassive){
  passive=isPassive;
}

bool FTPTransfer::isPassive() const{
  return passive;
}

bool FTPTransfer::openPassiveChanel(QString addr, quint16 port){
#ifdef FTPENGINE_DEBUG
  LogDebug()<<"openPassiveChanel("<<addr<<","<<port<<")";
#endif
  transfer=new QTcpSocket(this);
  connect(transfer,SIGNAL(readyRead()),SLOT(receivedTransferData()));
  connect(transfer,SIGNAL(readChannelFinished()),SLOT(disconnectTransfer()));
  connect(transfer,SIGNAL(bytesWritten(qint64)),
          SLOT(transferBytesWritten(qint64)));
  connect(transfer,SIGNAL(disconnected()),SLOT(transferConnectionClosed()));
#ifdef FTPENGINE_DEBUG
  connect(transfer,SIGNAL(error(QAbstractSocket::SocketError)),
          SLOT(transferError(QAbstractSocket::SocketError)));
  connect(transfer,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
          SLOT(transferSateChanged(QAbstractSocket::SocketState)));
#endif
  transfer->connectToHost(addr,port);
  bool res=transfer->waitForConnected();
  if(!res) errStr=transfer->errorString();
  return res;
}

void FTPTransfer::wait4communication(){
  if(m__State==State_None) return;
  loop->exec();
}

QString FTPTransfer::lastError() const{
  return errStr;
}

bool FTPTransfer::uploadNext()
{
  if ( (m__Client == NULL && !transfer) || m__Buffer == NULL ){
    errStr.clear();
    if(!m__Buffer) errStr=tr("Буфер не определён");
    if(!m__Client) errStr=tr("Клиентское подключение не определено");
    if(!transfer) errStr=tr("Канал передачи данных не определён");
    return false;
  }

  const qint64 blockSize = 16*1024;
  char buf[16*1024];
  qint64 read = m__Buffer->read(buf, blockSize);
  qint64 write = 0;
  if ( read > 0 ){
    if(isPassive()){
      if(!transfer) return false;
      write=transfer->write(buf,read);
    }else write = m__Client->write( buf, read );
  }else errStr=m__Buffer->errorString();
  if(write<=0)
    errStr=(isPassive()?"transfer: "+transfer->errorString():
                        "Client: "+m__Client->errorString());
  return ( write > 0 );
}

void FTPTransfer::incomingConnection()
{
  if ( !m__Server->hasPendingConnections() ) return;

  if ( m__Client != NULL )
  {
    m__Server->nextPendingConnection()->disconnectFromHost();
    return;
  }

  m__Client = m__Server->nextPendingConnection();
  connect( m__Client, SIGNAL(readyRead()), SLOT(receivedData()) );
  connect( m__Client, SIGNAL(readChannelFinished()), SLOT(disconnectClient()) );
  connect( m__Client, SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten(qint64)) );
  connect( m__Client, SIGNAL(disconnected()), SLOT(connectionClosed()) );
}

void FTPTransfer::receivedData()
{
  m__State = State_Communication;

  QByteArray data = QByteArray();
  data.append( m__Client->readAll() );

  m__Buffer->write( data );
  emit dataCommunicationProgress( m__Buffer->size(), 0 );
}

void FTPTransfer::receivedTransferData(){
  m__State = State_Communication;

  QByteArray data = QByteArray();
  data.append( transfer->readAll() );

  if(!m__Buffer){
    errStr=tr("Буфер не определён");
    return;
  }
  m__Buffer->write( data );
  emit dataCommunicationProgress( m__Buffer->size(), 0 );
}

void FTPTransfer::bytesWritten(qint64 size)
{
    m__BytesDone += size;
    dataCommunicationProgress( m__BytesDone, m__Buffer->size() );
    if ( m__BytesDone < m__Buffer->size() ) uploadNext();
    else disconnectClient();
}

void FTPTransfer::transferBytesWritten(qint64 size){
  m__BytesDone += size;
  if(!m__Buffer){
    errStr=tr("Буфер не определён");
    return;
  }
  dataCommunicationProgress( m__BytesDone, m__Buffer->size() );
  if ( m__BytesDone < m__Buffer->size() ) uploadNext();
  else disconnectTransfer();
}

void FTPTransfer::disconnectClient()
{
//  QByteArray data = QByteArray();
//  data.append( m__Client->readAll() );

//  m__Buffer->write( data );
  m__Buffer = NULL;
  m__BytesDone = 0;
  disconnect( m__Client, SIGNAL(readyRead()), this, SLOT(receivedData()) );
  disconnect( m__Client, SIGNAL(readChannelFinished()), this, SIGNAL(disconnectClient()) );
  disconnect( m__Client, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)) );
  m__Client->disconnectFromHost();
  emit dataCommunicationFinished();
}

void FTPTransfer::disconnectTransfer(){
  m__Buffer = NULL;
  m__BytesDone = 0;
  transfer->disconnect(this);
  transfer->disconnectFromHost();
  emit dataCommunicationFinished();
}

void FTPTransfer::connectionClosed()
{
  disconnect( m__Client, SIGNAL(readyRead()), this, SLOT(receivedData()) );
  disconnect( m__Client, SIGNAL(readChannelFinished()), this, SIGNAL(disconnectClient()) );
  disconnect( m__Client, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)) );
  disconnect( m__Client, SIGNAL(disconnected()), this, SLOT(connectionClosed()) );
  if ( m__Client != NULL )
  {
      m__Client->close();
      m__Client = NULL;
  }
  if ( m__State != State_None ) emit connectionTerminated();
  m__State = State_None;
  loop->quit();
}

void FTPTransfer::transferConnectionClosed(){
  transfer->disconnect(this);
  transfer->close();
  transfer->deleteLater();
  transfer=NULL;
  if(m__State!=State_None) emit connectionTerminated();
  m__State=State_None;
  loop->quit();
}

#ifdef FTPENGINE_DEBUG
void FTPTransfer::transferError(QAbstractSocket::SocketError err){
  LogDebug()<<err<<transfer->errorString();
}

void FTPTransfer::transferSateChanged(QAbstractSocket::SocketState st){
  LogDebug()<<"transfer state ="<<st;
}
#endif
