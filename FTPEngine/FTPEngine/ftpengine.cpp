#include "ftpengine.h"

#include <QDebug>

FTPEngine::FTPEngine( QObject *parent ) :
  QObject(parent)
{
  m__Url = QUrl();
  m__Port = -1;
  m__Socket = new QTcpSocket( this );
  m__Connected = false;

  m__User = QString();
  m__Password = QString();
  m__Authenticated = false;

  m__AccessManager = new QNetworkAccessManager( this );
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
//  qDebug() << "connectTo" << url;
//  m__Reply = m__AccessManager->get( QNetworkRequest( url ) );
//  connect( m__Reply, SIGNAL(finished()), this, SLOT(finished()) );
//  connect( m__Reply, SIGNAL(downloadProgress(qint64,qint64)),
//           this, SLOT(downloadProgress(qint64,qint64)) );
//  connect( m__Reply, SIGNAL(readyRead()),
//           this, SLOT(readyRead()) );
//  if ( m__Reply->error() != QNetworkReply::NoError )
//  {
//    qDebug() << "connectTo" << m__Reply->errorString();
//    return false;
//  }
//  else
//  {
//    qDebug() << "connectTo" << "Successfully opened!";
////    qDebug() << reply->write( "" )
//  }
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

  setDefaultConnect();
  connect( m__Socket, SIGNAL(readyRead()),
           this, SLOT(socketAllReply()) );

  m__Socket->write( tr( "%1\n" ).arg( text ).toLocal8Bit() );

  return true;
}

void FTPEngine::setDefaultConnect()
{
  connect( m__Socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
           this, SLOT(socketStateChanged(QAbstractSocket::SocketState)) );
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

  setDefaultConnect();
  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthUserReply()) );

  m__Socket->write( tr( "user %1\n" ).arg( m__User ).toLocal8Bit() );
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

  setDefaultConnect();
  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthPassReply()) );

  m__Socket->write( tr( "pass %1\n" ).arg( m__Password ).toLocal8Bit() );
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
  QByteArray answer = m__Socket->readAll().replace( "\n", "" );
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );
}

void FTPEngine::finished()
{
//  qDebug() << "finished" << m__Reply->readAll();
  qDebug() << "finished" << m__Reply->error();
  qDebug() << "finished" << m__Reply->errorString();
}

void FTPEngine::downloadProgress( qint64 current, qint64 max )
{
  qDebug() << "downloadProgress" << current << max;
}

void FTPEngine::readyRead()
{
  qDebug() << "readyRead" << m__Reply->readAll();
}
