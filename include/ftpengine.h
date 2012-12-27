#ifndef FTPENGINE_H
#define FTPENGINE_H

#include <QObject>

#ifdef FTPENGINE_LIBRARY
#define FTPENGINE_EXPORT Q_DECL_EXPORT
#else
#define FTPENGINE_EXPORT Q_DECL_IMPORT
#endif

#include "ftpfile.h"
#include "fileinfo.h"

#include <QDir>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QUrl>

class FTPCommand;
class FTPTransfer;

class FTPENGINE_EXPORT FTPEngine : public QObject
{
  Q_OBJECT
public:
  explicit FTPEngine( QObject *parent = 0 );
  ~FTPEngine();

  bool setTempDirectory( const QDir &dir = QDir( QCoreApplication::applicationDirPath()+tr( "/Temp" ) ) );

  void connectToHost( const QUrl &url = QUrl() , int port = 21 );
  void disconnectFromHost();
  bool isConnected() const;

  void setAuthentication( QString user, QString password );
  bool isAuthenticated() const;

  bool sendCommand( QString text );

  void path();
  void dir();
  void cd( QString path );
  void mkDir( QString name );
  void rmDir( QString name );
  void putFile( QString name );
  void rmFile( QString name );
  void getFile( QString name );

  bool hasDowloadedFiles() const;
  FTPFile * nextDowloadedFile();
  QList<FileInfo> dirResult();

signals:
  void authenticationRequired();
  void authenticationCompleted( bool );
  void executedCommand( QString text );
  void ftpAnswer( QString text );

  void ftpAnswer( QString command, bool result );
  void loadProgress( QString fileName, qint64 current,qint64 max );

public slots:

private:
  QDir m__TempDirectory;

  QUrl m__Url;
  int m__Port;
  QTcpSocket *m__Socket;
  bool m__Connected;

  QList<FTPCommand> m__PendingCommands;

  QString m__User;
  QString m__Password;
  bool m__Authenticated;

  FTPTransfer *m__Transfer;
  QList<FTPFile *> m__DownloadedFiles;

  void setDefaultConnect();

  void executeCommand( QString text );
  void nextCommand();

  int ftpAnswerCode( const QByteArray &answer );
  bool checkCode( const QByteArray &answer, int code );

  void authenticationStart();

private slots:
  void socketStateChanged( QAbstractSocket::SocketState socketState );

  void socketConnected();
  void socketAuthUserReply();
  void socketAuthPassReply();
  void socketAllReply();
};

#endif // FTPENGINE_H
