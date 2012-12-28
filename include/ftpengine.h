#ifndef FTPENGINE_H
#define FTPENGINE_H

#include <QObject>

#include "ftpengine_export.h"
#include "ftpfile.h"
#include "fileinfo.h"

#include <QDir>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QUrl>
#include <QTimer>

class FTPCommand;
class FTPTransfer;

class FTPENGINE_EXPORT FTPEngine : public QObject
{
  Q_OBJECT
public:
  enum Command {Command_None =	0, Command_User, Command_Password, Command_Path,
                Command_Quit, Command_List, Command_Cd, Command_Get,
                Command_Put, Command_Mkdir, Command_Rmdir};

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
  void list();
  void cd( QString path );
  void mkDir( QString name );
  void rmDir( QString name );
  void putFile( QString name );
  void rmFile( QString name );
  void getFile( QString name );

  QString lastError() const;
  QString lastText() const;

  bool hasDowloadedFiles() const;
  FTPFile * nextDowloadedFile();
  QList<FileInfo *> listResult();

signals:
  void authenticationRequired();
  void authenticationCompleted( bool );
  void executedCommand( QString text );
  void ftpAnswer( QString answerText );

  void ftpAnswer( FTPEngine::Command, bool result );
  void loadProgress( QString fileName, qint64 current,qint64 max );

public slots:

private:
  QDir m__TempDirectory;

  QUrl m__Url;
  int m__Port;
  QTcpSocket *m__Socket;
  bool m__Connected;

  FTPCommand *m__ActualCommand;
  FTPCommand *m__CurrentCommand;
  QList<FTPCommand *> m__PendingCommands;
  QString m__LastError;
  QString m__LastText;

  QString m__User;
  QString m__Password;
  bool m__Authenticated;

  FTPTransfer *m__Transfer;
  QList<FTPFile *> m__DownloadedFiles;
  QByteArray m__DirData;
  QList<FileInfo *> m__DirInfo;

  QTimer *m__Timer;

  void setDefaultConnect();

  void executeCommand( QString text );
  void clearPendingCommands();

  int ftpAnswerCode( const QByteArray &answer );
  QString ftpAnswerText( const QByteArray &answer );
  bool checkCode( const QByteArray &answer, int code );

  void authenticationStart();

  bool parseDir( const QByteArray &buffer, const QString &userName, FileInfo *info );

  Command getCommand() const;

private slots:
  void socketStateChanged( QAbstractSocket::SocketState socketState );

  void socketConnected();
  void socketAuthUserReply();
  void socketAuthPassReply();
  void socketAllReply();

  void nextCommand();

  void transferData( QByteArray data );
  void transferDataFinished();
};

#endif // FTPENGINE_H
