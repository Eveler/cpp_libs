#include "ftptransfer.h"

FTPTransfer::FTPTransfer(QObject *parent) :
  QObject(parent),
  m__Server(new QTcpServer),
  m__Client(NULL),
  m__State(FTPTransfer::State_None),
  m__Buffer(NULL),
  m__BytesDone(0)
{
  connect( m__Server, SIGNAL(newConnection()), SLOT(incomingConnection()) );
}

FTPTransfer::~FTPTransfer()
{
  delete m__Server;
  m__Server = NULL;
  m__Client = NULL;
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

bool FTPTransfer::uploadNext()
{
  if ( m__Client == NULL || m__Buffer == NULL ) return false;

  const qint64 blockSize = 16*1024;
  char buf[16*1024];
  qint64 read = m__Buffer->read(buf, blockSize);
  qint64 write = 0;
  if ( read > 0 ) write = m__Client->write( buf, read );
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

void FTPTransfer::bytesWritten(qint64 size)
{
    m__BytesDone += size;
    dataCommunicationProgress( m__BytesDone, m__Buffer->size() );
    if ( m__BytesDone < m__Buffer->size() ) uploadNext();
    else disconnectClient();
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
}
