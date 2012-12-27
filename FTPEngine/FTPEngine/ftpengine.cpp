#include "ftpengine.h"

#include "ftpcommand.h"
#include "ftptransfer.h"

#include <QDebug>
#include <QHostAddress>

FTPEngine::FTPEngine( QObject *parent ) :
  QObject(parent),
  m__Socket(new QTcpSocket),
  m__Transfer(new FTPTransfer( m__Socket->localAddress() ))
{
  m__Url = QUrl();
  m__Port = -1;
  m__Connected = false;

  m__User = QString();
  m__Password = QString();
  m__Authenticated = false;
}

FTPEngine::~FTPEngine()
{
  delete m__Socket;
  delete m__Transfer;
}

bool FTPEngine::setTempDirectory( const QDir &dir )
{
  if ( !m__TempDirectory.entryList().isEmpty() ||
       !dir.exists() && !dir.mkpath( dir.absolutePath() ) ) return false;

  m__TempDirectory.setPath( dir.absolutePath() );
}

void FTPEngine::connectToHost( const QUrl &url, int port )
{
  m__Url = url;
  m__Port = port;

  m__Socket->disconnect();

  if ( m__Url.isEmpty() || m__Port == -1 ) return;

  if ( m__Socket->state() != QAbstractSocket::UnconnectedState ) return;

  setDefaultConnect();
  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketConnected()) );

  m__Socket->connectToHost( m__Url.host(), m__Port );
}

void FTPEngine::disconnectFromHost()
{
  if ( m__Socket->state() != QAbstractSocket::UnconnectedState )
    m__Socket->disconnectFromHost();

  m__Socket->disconnect();
}

bool FTPEngine::isConnected() const
{
  return m__Connected;
}

void FTPEngine::setAuthentication( QString user, QString password )
{
  m__User = user;
  m__Password = password;
  m__Authenticated = false;

  if ( isConnected() ) authenticationStart();
  else connectToHost( m__Url, m__Port );
}

bool FTPEngine::isAuthenticated() const
{
  return m__Authenticated;
}

bool FTPEngine::sendCommand( QString text )
{
  m__Socket->disconnect();

  if ( !isConnected() ) return false;

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAllReply()) );

  executeCommand( tr( "%1\n" ).arg( text ) );

  return true;
}

bool FTPEngine::hasDowloadedFiles() const
{
  return !m__DownloadedFiles.isEmpty();
}

FTPFile * FTPEngine::nextDowloadedFile()
{
  FTPFile *result = m__DownloadedFiles.takeFirst();
  result->setParent( NULL );
  return result;
}

void FTPEngine::setDefaultConnect()
{
  connect( m__Socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
           this, SLOT(socketStateChanged(QAbstractSocket::SocketState)) );
}

void FTPEngine::executeCommand( QString text )
{
  setDefaultConnect();
  QString command = text;
  text = text.replace( "\r", "" ).replace( "\n", "" );
  emit executedCommand( text );
  m__Socket->write( command.toLatin1() );
}

void FTPEngine::nextCommand()
{
  if ( m__PendingCommands.isEmpty() ) return;

  FTPCommand command = m__PendingCommands.takeFirst();
  executeCommand( QString( "%1 %2\n" ).arg( command.name().toUpper(), command.argument() ) );
}

int FTPEngine::ftpAnswerCode( const QByteArray &answer )
{
  return answer.split( ' ' ).first().toInt();
}

bool FTPEngine::checkCode( const QByteArray &answer, int code )
{
  int ansCode = ftpAnswerCode( answer );
  if ( ansCode != code )
  {
    qDebug() << "Unknown FTP-answer code:" << code;
    return false;
  }

  return true;
}

void FTPEngine::authenticationStart()
{
  if ( m__User.isEmpty() )
  {
    emit authenticationRequired();
    return;
  }

  m__Socket->disconnect();

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthUserReply()) );

  executeCommand( tr( "user %1\n" ).arg( m__User ) );
}

void FTPEngine::socketStateChanged( QAbstractSocket::SocketState socketState )
{
  qDebug() << "socketStateChanged" << socketState;

  m__Connected = ( socketState == QAbstractSocket::ConnectedState );

  if ( !m__Connected ) m__Authenticated = false;
}

void FTPEngine::socketConnected()
{
  QByteArray answer = m__Socket->readAll().replace( "\n", "" );
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );

  if ( !checkCode( answer, 220 ) ) return;

  authenticationStart();
}

void FTPEngine::socketAuthUserReply()
{
  QByteArray answer = m__Socket->readAll().replace( "\n", "" );
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );

  if ( !checkCode( answer, 331 ) ) return;

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthPassReply()) );

  executeCommand( tr( "pass %1\n" ).arg( m__Password ) );
}

void FTPEngine::socketAuthPassReply()
{
  QByteArray answer = m__Socket->readAll().replace( "\n", "" );
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );

  if ( !checkCode( answer, 230 ) )
  {
    emit authenticationCompleted( m__Authenticated );
    return;
  }

  setDefaultConnect();

  m__Authenticated = true;
  emit authenticationCompleted( m__Authenticated );
}

void FTPEngine::socketAllReply()
{
  QByteArray answer = QByteArray();
  while ( m__Socket->canReadLine() )
    answer += m__Socket->readAll();
  answer = answer.replace( "\n", "" );
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );
}
