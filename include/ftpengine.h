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

  void connectToHost( const QUrl &url = QUrl() , int port = 21 );
  void disconnectFromHost();
  bool isConnected() const;

  void setAuthentication( QString user, QString password );
  bool isAuthenticated() const;

  bool sendCommand( QString text );

signals:
  void authenticationRequired();
  void authenticationCompleted( bool );
  void ftpAnswer( QString text );

public slots:

private:
  QUrl m__Url;
  int m__Port;
  QTcpSocket *m__Socket;
  bool m__Connected;

  QString m__User;
  QString m__Password;
  bool m__Authenticated;

  QNetworkAccessManager *m__AccessManager;
  QNetworkReply *m__Reply;

  void setDefaultConnect();

  int ftpAnswerCode( const QByteArray &answer );
  bool checkCode( const QByteArray &answer, int code );

  void authenticationStart();

private slots:
  void socketStateChanged( QAbstractSocket::SocketState socketState );

  void socketConnected();
  void socketAuthUserReply();
  void socketAuthPassReply();
  void socketAllReply();

  void finished();
  void downloadProgress( qint64 current,qint64 max );


  void readyRead();
};

#endif // FTPENGINE_H
