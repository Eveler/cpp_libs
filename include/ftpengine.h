#ifndef FTPENGINE_H
#define FTPENGINE_H

#include <QObject>

#include "ftpengine_export.h"
#include "fileinfo.h"

#include <QDir>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QUrl>
#include <QTimer>
#include <QIODevice>

class FTPCommand;
class FTPCommandsPool;
class FTPTransfer;

class FTPENGINE_EXPORT FTPEngine : public QObject
{
  Q_OBJECT
public:
  enum Command {Command_None =	0, Command_User, Command_Password, Command_Path,
                Command_Quit, Command_List, Command_Cd, Command_SizeOf,
                Command_PutFile, Command_RmFile, Command_GetFile, Command_MkDir, Command_RmDir};

  explicit FTPEngine( QObject *parent = 0 );
  ~FTPEngine();

  void connectToHost( const QUrl &url = QUrl() , int port = 21 );
  void disconnectFromHost();
  bool isConnected() const;

  void setAuthentication( QString user, QString password );
  bool isAuthenticated() const;

  void setBuffer( QIODevice *buffer );
  QIODevice * buffer() const;
  bool sendCommand( QString text, bool ignoreError = false );

  bool path();
  bool list();
  bool cd( QString path );
  bool mkDir( QString name, bool ignoreError = false );
  bool rmDir( QString name );
  bool sizeOf( QString name );
  bool putFile( QString name, QIODevice *buffer );
  bool putFiles( QStringList names , QList<QIODevice *> buffers );
  bool rmFile( QString name );
  bool getFile( QString name, QIODevice *buffer );
  bool getFiles( QStringList names , QList<QIODevice *> buffers );
  void beginCommands();
  void sendCommands();

  QString lastError() const;
  QString lastText() const;

  QList<FileInfo *> listResult();

  bool isFinished();

signals:
  void authenticationRequired();
  void authenticationCompleted( bool );
  void executedCommand( QString text );
  void ftpAnswer( QString answerText );

  void ftpAnswer( FTPEngine::Command, bool result );
  void loadProgress( QString fileName, qint64 current,qint64 max );

public slots:

private:
  QUrl m__Url;
  int m__Port;
  QTcpSocket *m__Socket;
  bool m__Connected;

  QList<FTPCommandsPool *> m__Commands;
  FTPCommandsPool *m__CurrentCommand;
  QString m__LastError;
  QString m__LastText;

  QString m__User;
  QString m__Password;
  bool m__Authenticated;

  FTPTransfer *m__Transfer;
  QIODevice *m__Buffer;
  QHash<FTPCommand *, QPair<FileInfo *, QIODevice *> > m__CommandIODevice;
  QByteArray m__DirData;
  QList<FileInfo *> m__DirInfo;

  QTimer *m__Timer;

  bool m__CommandListCreation;

  void setDefaultConnect();

  void executeCommand( QString text );
  void clearCommands();

  FTPCommandsPool * putFile_P( QString name, QIODevice *buffer );
  FTPCommandsPool * getFile_P( QString name, QIODevice *buffer );

  int ftpAnswerCode( const QByteArray &answer );
  QString ftpAnswerText( const QByteArray &answer );
  bool checkCode( const QByteArray &answer, int code );

  void authenticationStart();

  bool parseDir( const QByteArray &buffer, const QString &userName, FileInfo *info );

  Command getCommand() const;

  void sendAnswerResult( bool result );

private slots:
  void socketStateChanged( QAbstractSocket::SocketState socketState );

  void socketConnected();
  void socketAuthUserReply();
  void socketAuthPassReply();
  void socketAllReply();

  void nextCommand();

  void transferDataProgress( qint64 currentSize, qint64 overallSize );
  void transferDataFinished();
};

#endif // FTPENGINE_H
