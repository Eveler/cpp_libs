#ifndef FTPENGINE_H
#define FTPENGINE_H

#include <QObject>

#ifdef FTPENGINE_LIBRARY
#define FTPENGINE_EXPORT Q_DECL_EXPORT
#else
#define FTPENGINE_EXPORT Q_DECL_IMPORT
#endif

#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>

class FTPENGINE_EXPORT FTPEngine : public QObject
{
  Q_OBJECT
public:
  explicit FTPEngine( QObject *parent = 0 );

//  void setAuthenticator( QAuthenticator *authenticator );
//  QAuthenticator * authenticator() const;

  void setAuthentication( QString user, QString password );
  void connectTo( const QUrl &url = QUrl() , int port = 21 );

signals:
  void authenticationRequired();

public slots:

private:
  QTcpSocket *m__Socket;

  QString m__User;
  QString m__Password;

  QNetworkAccessManager *m__AccessManager;
  QNetworkReply *m__Reply;

  void authenticationStart();

private slots:
  void socketStateChanged( QAbstractSocket::SocketState socketState );
  void socketConnected();

  void socketAuthUserReply();
  void socketAuthPassReply();

  void finished();
  void downloadProgress( qint64 current,qint64 max );


  void readyRead();
};

#endif // FTPENGINE_H
