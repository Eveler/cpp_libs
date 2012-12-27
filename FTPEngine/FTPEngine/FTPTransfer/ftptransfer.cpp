#include "ftptransfer.h"

FTPTransfer::FTPTransfer(QHostAddress localAddress, QObject *parent) :
  QObject(parent),
  m__Server(new QTcpServer),
  m__Client(NULL),
  m__State(FTPTransfer::State_None)
{
  connect( m__Server, SIGNAL(newConnection()), SLOT(incomingConnection()) );
  m__Server->listen( localAddress );
}

FTPTransfer::~FTPTransfer()
{
  delete m__Server;
  m__Server = NULL;
  m__Client = NULL;
}

quint16 FTPTransfer::port() const
{
  return m__Server->serverPort();
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
  connect( m__Client, SIGNAL(disconnected()), SLOT(connectionClosed()) );
}

void FTPTransfer::receivedData()
{
  m__State = State_Communication;

  QByteArray data = QByteArray();
  while ( m__Client->readBufferSize() > 0 )
    data.append( m__Client->readAll() );

  emit downloadedData( data );
}

void FTPTransfer::connectionClosed()
{
  disconnect( m__Client, SIGNAL(readyRead()), this, SLOT(receivedData()) );
  disconnect( m__Client, SIGNAL(disconnected()), this, SLOT(connectionClosed()) );
  m__Client = NULL;
  if ( m__State != State_None ) emit connectionTerminated();
  m__State = State_None;
}
