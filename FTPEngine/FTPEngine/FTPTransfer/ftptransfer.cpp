#include "ftptransfer.h"

FTPTransfer::FTPTransfer(QObject *parent) :
  QObject(parent),
  m__Server(new QTcpServer),
  m__Client(NULL),
  m__State(FTPTransfer::State_None)
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
//  qDebug() << __LINE__ << __FILE__ << localAddress;
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

bool FTPTransfer::uploadData( const QByteArray &data )
{
  if ( m__Client == NULL ) return false;

  qint64 res = m__Client->write( data ) != -1;
  m__Client->waitForBytesWritten();
  return ( res != -1 );
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
  connect( m__Client, SIGNAL(disconnected()), SLOT(connectionClosed()) );
}

void FTPTransfer::receivedData()
{
  m__State = State_Communication;

  QByteArray data = QByteArray();
  while ( m__Client->canReadLine() )
    data.append( m__Client->readAll() );

//  qDebug() << __FILE__ << __LINE__ << data;
  emit downloadedData( data );
}

void FTPTransfer::disconnectClient()
{
  emit readChannelFinished();
  m__Client->disconnectFromHost();
}

void FTPTransfer::connectionClosed()
{
  disconnect( m__Client, SIGNAL(readyRead()), this, SLOT(receivedData()) );
  disconnect( m__Client, SIGNAL(readChannelFinished()), this, SIGNAL(readChannelFinished()) );
  disconnect( m__Client, SIGNAL(readyRead()), this, SLOT(receivedData()) );
  m__Client = NULL;
  if ( m__State != State_None ) emit connectionTerminated();
  m__State = State_None;
}
