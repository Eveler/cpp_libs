#include "ftpengine.h"

#include <QDebug>

FTPEngine::FTPEngine( QObject *parent ) :
  QObject(parent)
{
  m__Socket = new QTcpSocket( this );

  m__User = QString();
  m__Password = QString();

  m__AccessManager = new QNetworkAccessManager( this );
}

void FTPEngine::setAuthentication( QString user, QString password )
{
  m__User = user;
  m__Password = password;

  qDebug() << user << password;
  if ( m__Socket->state() == QAbstractSocket::ConnectedState ) authenticationStart();
}

void FTPEngine::connectTo( const QUrl &url, int port )
{
  if ( m__Socket->state() != QAbstractSocket::UnconnectedState )
    m__Socket->disconnectFromHost();

  m__Socket->disconnect();

  connect( m__Socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
           this, SLOT(socketStateChanged(QAbstractSocket::SocketState)) );
  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketConnected()) );

  m__Socket->connectToHost( url.host(), port );
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

void FTPEngine::authenticationStart()
{
  if ( m__User.isEmpty() )
  {
    qDebug() << "authenticationRequired";
    emit authenticationRequired();
    return;
  }

  m__Socket->disconnect();

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthUserReply()) );

  m__Socket->write( tr( "user %1\n" ).arg( m__User ).toLocal8Bit() );
}

void FTPEngine::socketStateChanged( QAbstractSocket::SocketState socketState )

{
  qDebug() << "socketStateChanged" << socketState;
}

void FTPEngine::socketConnected()
{
  qDebug() << "FTP answer" << m__Socket->readAll();

  authenticationStart();
}

void FTPEngine::socketAuthUserReply()
{
  qDebug() << "FTP answer" << m__Socket->readAll();

  m__Socket->disconnect();

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthPassReply()) );

  m__Socket->write( tr( "pass %1\n" ).arg( m__Password ).toLocal8Bit() );
}

void FTPEngine::socketAuthPassReply()
{
  qDebug() << "FTP answer" << m__Socket->readAll();

  m__Socket->disconnect();
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
