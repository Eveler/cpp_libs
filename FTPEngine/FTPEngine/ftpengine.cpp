#include "ftpengine.h"

#include "ftpcommand.h"
#include "ftptransfer.h"

#include <QHostAddress>
#include <QBuffer>

#include <QDebug>

FTPEngine::FTPEngine( QObject *parent ) :
  QObject(parent),
  m__Socket(new QTcpSocket),
  m__ActualCommand(NULL),
  m__CurrentCommand(NULL),
  m__Transfer(new FTPTransfer),
  m__Buffer(NULL),
  m__DirData(QByteArray()),
  m__DirInfo(QList<FileInfo *>()),
  m__Timer(new QTimer)
{
  m__Url = QUrl();
  m__Port = -1;
  m__Connected = false;

  m__User = QString();
  m__Password = QString();
  m__Authenticated = false;

  connect( m__Transfer, SIGNAL(dataCommunicationProgress(qint64,qint64)),
           SLOT(transferDataProgress(qint64,qint64)) );
  connect( m__Transfer, SIGNAL(dataCommunicationFinished()),
           SLOT(transferDataFinished()) );
}

FTPEngine::~FTPEngine()
{
  delete m__Socket;
  m__Socket = NULL;
  delete m__Transfer;
  m__Transfer = NULL;
  m__Buffer = NULL;

  clearPendingCommands();
  m__ActualCommand = NULL;
  if ( m__CurrentCommand != NULL ) delete m__CurrentCommand;
  m__CurrentCommand = NULL;

  delete m__Timer;
  m__Timer = NULL;
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

void FTPEngine::setBuffer( QIODevice *buffer )
{
  m__Buffer = buffer;
}

QIODevice * FTPEngine::buffer() const
{
  return m__Buffer;
}

bool FTPEngine::sendCommand( QString text )
{
  m__Socket->disconnect();

  if ( !isConnected() )
  {
      qDebug() << "Not connected!";
      return false;
  }

  QStringList cmd = text.split( " " );
  QString cmdText = cmd.first();
  cmd.removeFirst();
  QString cmdArg = cmd.join( " " );

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAllReply()) );

  if ( cmdText == FTPCommand::name( FTPCommand::Type_Pwd ) ) path();
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_List ) ) list();
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Cwd ) ) cd( cmdArg );
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Mkd ) ) mkDir( cmdArg );
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Rmd ) ) rmDir( cmdArg );
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Size ) ) sizeOf( cmdArg );
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Stor ) )
  {
    if ( m__Buffer == NULL || !m__Buffer->isOpen() ) return false;
    putFile( cmdArg, m__Buffer );
  }
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Dele ) ) rmFile( cmdArg );
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Retr ) )
  {
    if ( m__Buffer == NULL || !m__Buffer->isOpen() ) return false;
    getFile( cmdArg, m__Buffer );
  }
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Cdup ) )
  {
    m__PendingCommands << new FTPCommand( FTPCommand::Type_Cdup );

    nextCommand();
  }
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Type ) )
  {
    m__PendingCommands << new FTPCommand( FTPCommand::Type_Type, cmdArg );

    nextCommand();
  }
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Port ) )
  {
    QString argument = m__Transfer->address().toString().replace( ".", "," );
    argument += ","+QString::number((m__Transfer->port() & 0xff00) >> 8);
    argument += ","+QString::number(m__Transfer->port() & 0xff);
    m__PendingCommands << new FTPCommand( FTPCommand::Type_Port, argument );

    nextCommand();
  }
  else if ( cmdText == FTPCommand::name( FTPCommand::Type_Quit ) )
  {
    m__PendingCommands << new FTPCommand( FTPCommand::Type_Quit );

    nextCommand();
  }
  else executeCommand( tr( "%1\r\n" ).arg( text ) );

  return true;
}

bool FTPEngine::path()
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Pwd );

  nextCommand();

  return true;
}

bool FTPEngine::list()
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Type, tr( "a" ), true );
  QString argument = m__Transfer->address().toString().replace( ".", "," );
  argument += ","+QString::number((m__Transfer->port() & 0xff00) >> 8);
  argument += ","+QString::number(m__Transfer->port() & 0xff);
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Port, argument, true );
  FTPCommand *mainCommand = new FTPCommand( FTPCommand::Type_List );
  m__PendingCommands << mainCommand;
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Noop, QString(), true );

  FileInfo *fi = NULL;
  QIODevice *buffer = new QBuffer( &m__DirData, this );
  buffer->open( QIODevice::WriteOnly );
  m__CommandIODevice.insert( mainCommand, qMakePair( fi, buffer ) );

  nextCommand();

  return true;
}

bool FTPEngine::cd( QString path )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Cwd, path );

  nextCommand();

  return true;
}

bool FTPEngine::mkDir( QString name )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Mkd, name );

  nextCommand();

  return true;
}

bool FTPEngine::rmDir( QString name )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Rmd, name );

  nextCommand();

  return true;
}

bool FTPEngine::sizeOf( QString name )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Type, tr( "i" ), true );
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Size, name );

  nextCommand();

  return true;
}

bool FTPEngine::putFile( QString name , QIODevice *buffer )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Type, tr( "i" ), true );
  QString argument = m__Transfer->address().toString().replace( ".", "," );
  argument += ","+QString::number((m__Transfer->port() & 0xff00) >> 8);
  argument += ","+QString::number(m__Transfer->port() & 0xff);
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Port, argument, true );
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Allo, QString::number( buffer->size() ), true );
  FTPCommand *mainCommand = new FTPCommand( FTPCommand::Type_Stor, name );
  m__PendingCommands << mainCommand;
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Noop, QString(), true );

  FileInfo *fi = new FileInfo;
  QString fileName = mainCommand->argument();
  fileName = fileName.replace( "\"", "" );
  qint64 fileSize = buffer->size();
  fi->setFileName( fileName );
  fi->setSize( fileSize );
  m__CommandIODevice.insert( mainCommand, qMakePair( fi, buffer ) );

  nextCommand();

  return true;
}

bool FTPEngine::rmFile( QString name )
{
  if ( !isConnected() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Dele, name, true );

  nextCommand();

  return true;
}

bool FTPEngine::getFile( QString name, QIODevice *buffer )
{
  if ( !isConnected() ) return false;
  if ( buffer == NULL || !buffer->isOpen() ) return false;

  m__PendingCommands << new FTPCommand( FTPCommand::Type_Type, tr( "i" ), true );
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Size, name, true );
  QString argument = m__Transfer->address().toString().replace( ".", "," );
  argument += ","+QString::number((m__Transfer->port() & 0xff00) >> 8);
  argument += ","+QString::number(m__Transfer->port() & 0xff);
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Port, argument, true );
  FTPCommand *mainCommand = new FTPCommand( FTPCommand::Type_Retr, name );
  m__PendingCommands << mainCommand;
  m__PendingCommands << new FTPCommand( FTPCommand::Type_Noop, QString(), true );

  FileInfo *fi = new FileInfo;
  m__CommandIODevice.insert( mainCommand, qMakePair( fi, buffer ) );

  nextCommand();

  return true;
}

QString FTPEngine::lastError() const
{
  return m__LastError;
}

QString FTPEngine::lastText() const
{
  return m__LastText;
}

QList<FileInfo *> FTPEngine::listResult()
{
  QList<FileInfo *> result = m__DirInfo;
  m__DirInfo.clear();
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
  qDebug() << "------>" << text;
  emit executedCommand( text );
  m__Socket->write( command.toLatin1() );
}

void FTPEngine::clearPendingCommands()
{
  while ( !m__PendingCommands.isEmpty() )
  {
    FTPCommand *command = m__PendingCommands.takeFirst();
    delete command;
  }
}

int FTPEngine::ftpAnswerCode( const QByteArray &answer )
{
  return answer.left( 3 ).toInt();
}

QString FTPEngine::ftpAnswerText( const QByteArray &answer )
{
  return QVariant( answer ).toString().mid( 3 ).trimmed();
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

static void _q_fixupDateTime(QDateTime *dateTime, bool leapYear = false)
{
    // Adjust for future tolerance.
    const int futureTolerance = 86400;
    if (dateTime->secsTo(QDateTime::currentDateTime()) < -futureTolerance) {
        QDate d = dateTime->date();
        if (leapYear) {
            int prevLeapYear = d.year() - 1;

            while (!QDate::isLeapYear(prevLeapYear))
               prevLeapYear--;

            d.setDate(prevLeapYear, d.month(), d.day());
        } else {
            d.setDate(d.year() - 1, d.month(), d.day());
        }
        dateTime->setDate(d);
    }
}

static void _q_parseUnixDir(const QStringList &tokens, const QString &userName, FileInfo *info)
{
    // Unix style, 7 + 1 entries
    // -rw-r--r--    1 ftp      ftp      17358091 Aug 10  2004 qt-x11-free-3.3.3.tar.gz
    // drwxr-xr-x    3 ftp      ftp          4096 Apr 14  2000 compiled-examples
    // lrwxrwxrwx    1 ftp      ftp             9 Oct 29  2005 qtscape -> qtmozilla
    if (tokens.size() != 8)
        return;

    char first = tokens.at(1).at(0).toLatin1();
    if (first == 'd') {
        info->setIsFile(false);
        info->setIsSymLink(false);
    } else if (first == '-') {
        info->setIsFile(true);
        info->setIsSymLink(false);
    } else if (first == 'l') {
        info->setIsFile(false);
        info->setIsSymLink(true);
    }

    // Resolve filename
    QString name = tokens.at(7);
    if (info->isSymLink()) {
        int linkPos = name.indexOf(QLatin1String(" ->"));
        if (linkPos != -1)
            name.resize(linkPos);
    }
    info->setFileName(name);

    // Resolve owner & group
    info->setOwner(tokens.at(3));
    info->setGroup(tokens.at(4));

    // Resolve size
    info->setSize(tokens.at(5).toLongLong());

    QStringList formats;
    formats << QLatin1String("MMM dd  yyyy") << QLatin1String("MMM dd hh:mm") <<
               QLatin1String("MMM  d  yyyy") << QLatin1String("MMM  d hh:mm") <<
               QLatin1String("MMM  d yyyy") << QLatin1String("MMM dd yyyy");

    QString dateString = tokens.at(6);
    dateString[0] = dateString[0].toUpper();

    // Resolve the modification date by parsing all possible formats
    QDateTime dateTime;
    int n = 0;
#ifndef QT_NO_DATESTRING
    do {
        dateTime = QLocale::c().toDateTime(dateString, formats.at(n++));
    }  while (n < formats.size() && (!dateTime.isValid()));
#endif

    if (n == 2 || n == 4) {
        // Guess the year.
        dateTime.setDate(QDate(QDate::currentDate().year(),
                               dateTime.date().month(),
                               dateTime.date().day()));
        _q_fixupDateTime(&dateTime);
    }
    if (dateTime.isValid())
        info->setLastModified(dateTime);
    else if (dateString.startsWith(QLatin1String("Feb 29"))) {

       // When the current year on the FTP server is a leap year and a
       // file's last modified date is Feb 29th, and the current day on
       // the FTP server is also Feb 29th, then the date can be in
       // formats n==2 or n==4. toDateTime in that case defaults to 1900
       // for the missing year. Feb 29 1900 is an invalid date and so
       // wont be parsed. This adds an exception that handles it.

       int recentLeapYear;
       QString timeString = dateString.mid(7);

       dateTime = QLocale::c().toDateTime(timeString, QLatin1String("hh:mm"));

       recentLeapYear = QDate::currentDate().year();

       while (!QDate::isLeapYear(recentLeapYear))
           recentLeapYear--;

       dateTime.setDate(QDate(recentLeapYear, 2, 29));

       _q_fixupDateTime(&dateTime, true);
       info->setLastModified(dateTime);
    }

    // Resolve permissions
    int permissions = 0;
    QString p = tokens.at(2);
    permissions |= (p[0] == QLatin1Char('r') ? QFileDevice::ReadOwner : 0);
    permissions |= (p[1] == QLatin1Char('w') ? QFileDevice::WriteOwner : 0);
    permissions |= (p[2] == QLatin1Char('x') ? QFileDevice::ExeOwner : 0);
    permissions |= (p[3] == QLatin1Char('r') ? QFileDevice::ReadGroup : 0);
    permissions |= (p[4] == QLatin1Char('w') ? QFileDevice::WriteGroup : 0);
    permissions |= (p[5] == QLatin1Char('x') ? QFileDevice::ExeGroup : 0);
    permissions |= (p[6] == QLatin1Char('r') ? QFileDevice::ReadOther : 0);
    permissions |= (p[7] == QLatin1Char('w') ? QFileDevice::WriteOther : 0);
    permissions |= (p[8] == QLatin1Char('x') ? QFileDevice::ExeOther : 0);
    info->setPermissions(permissions);

    bool isOwner = info->owner() == userName;
    info->setReadable((permissions & QFileDevice::ReadOther) ||
                      ((permissions & QFileDevice::ReadOwner) && isOwner));
    info->setWritable((permissions & QFileDevice::WriteOther) ||
                      ((permissions & QFileDevice::WriteOwner) && isOwner));
}

static void _q_parseDosDir(const QStringList &tokens, const QString &userName, FileInfo *info)
{
    // DOS style, 3 + 1 entries
    // 01-16-02  11:14AM       <DIR>          epsgroup
    // 06-05-03  03:19PM                 1973 readme.txt
    if (tokens.size() != 4)
        return;

    Q_UNUSED(userName);

    QString name = tokens.at(3);
    info->setFileName(name);
    info->setIsSymLink(name.toLower().endsWith(QLatin1String(".lnk")));

    if (tokens.at(2) == QLatin1String("<DIR>")) {
        info->setIsFile(false);
    } else {
        info->setIsFile(true);
        info->setSize(tokens.at(2).toLongLong());
    }

    // Note: We cannot use QFileInfo; permissions are for the server-side
    // machine, and QFileInfo's behavior depends on the local platform.
    int permissions = QFileDevice::ReadOwner | QFileDevice::WriteOwner
                      | QFileDevice::ReadGroup | QFileDevice::WriteGroup
                      | QFileDevice::ReadOther | QFileDevice::WriteOther;
    QString ext;
    int extIndex = name.lastIndexOf(QLatin1Char('.'));
    if (extIndex != -1)
        ext = name.mid(extIndex + 1);
    if (ext == QLatin1String("exe") || ext == QLatin1String("bat") || ext == QLatin1String("com"))
        permissions |= QFileDevice::ExeOwner | QFileDevice::ExeGroup | QFileDevice::ExeOther;
    info->setPermissions(permissions);

    info->setReadable(true);
    info->setWritable(info->isFile());

    QDateTime dateTime;
#ifndef QT_NO_DATESTRING
    dateTime = QLocale::c().toDateTime(tokens.at(1), QLatin1String("MM-dd-yy  hh:mmAP"));
    if (dateTime.date().year() < 1971) {
        dateTime.setDate(QDate(dateTime.date().year() + 100,
                               dateTime.date().month(),
                               dateTime.date().day()));
    }
#endif

    info->setLastModified(dateTime);

}

bool FTPEngine::parseDir( const QByteArray &buffer, const QString &userName, FileInfo *info )
{
    if (buffer.isEmpty())
        return false;

    QString bufferStr = QString::fromLatin1(buffer).trimmed();

    // Unix style FTP servers
    QRegExp unixPattern(QLatin1String("^([\\-dl])([a-zA-Z\\-]{9,9})\\s+\\d+\\s+(\\S*)\\s+"
                                      "(\\S*)\\s+(\\d+)\\s+(\\S+\\s+\\S+\\s+\\S+)\\s+(\\S.*)"));
    if (unixPattern.indexIn(bufferStr) == 0) {
        _q_parseUnixDir(unixPattern.capturedTexts(), userName, info);
        return true;
    }

    // DOS style FTP servers
    QRegExp dosPattern(QLatin1String("^(\\d\\d-\\d\\d-\\d\\d\\ \\ \\d\\d:\\d\\d[AP]M)\\s+"
                                     "(<DIR>|\\d+)\\s+(\\S.*)$"));
    if (dosPattern.indexIn(bufferStr) == 0) {
        _q_parseDosDir(dosPattern.capturedTexts(), userName, info);
        return true;
    }

    // Unsupported
    return false;
}

FTPEngine::Command FTPEngine::getCommand() const
{
  if ( m__CurrentCommand == NULL ) return Command_None;
  switch ( m__CurrentCommand->type() )
  {
  case FTPCommand::Type_User:
    return Command_User;
  case FTPCommand::Type_Pass:
    return Command_Password;
  case FTPCommand::Type_Pwd:
    return Command_Path;
  case FTPCommand::Type_Cwd:
    return Command_Cd;
  case FTPCommand::Type_List:
    return Command_List;
  case FTPCommand::Type_Mkd:
    return Command_MkDir;
  case FTPCommand::Type_Rmd:
    return Command_RmDir;
  case FTPCommand::Type_Size:
    return Command_SizeOf;
  case FTPCommand::Type_Stor:
    return Command_PutFile;
  case FTPCommand::Type_Dele:
    return Command_RmFile;
  case FTPCommand::Type_Retr:
    return Command_GetFile;
  case FTPCommand::Type_Quit:
    return Command_Quit;
  }

  return Command_None;
}

void FTPEngine::sendAnswerResult( bool result )
{
    Command currentCommand = getCommand();
    if ( m__ActualCommand == m__CurrentCommand )
    {
      delete m__ActualCommand;
      m__ActualCommand = NULL;
      m__CurrentCommand = NULL;
    }
    else
    {
      delete m__ActualCommand;
      m__ActualCommand = NULL;
      delete m__CurrentCommand;
      m__CurrentCommand = NULL;
    }
    emit ftpAnswer( currentCommand, result );
}

void FTPEngine::socketStateChanged( QAbstractSocket::SocketState socketState )
{
  qDebug() << "socketStateChanged" << socketState;

  m__Connected = ( socketState == QAbstractSocket::ConnectedState );

  if ( !m__Connected ) m__Authenticated = false;
}

void FTPEngine::socketConnected()
{
  QByteArray answer = m__Socket->readAll().trimmed();
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  m__Transfer->listen( m__Socket->localAddress() );

  emit ftpAnswer( QVariant( answer ).toString() );

  if ( !checkCode( answer, 220 ) ) return;

  authenticationStart();
}

void FTPEngine::socketAuthUserReply()
{
  QByteArray answer = m__Socket->readAll().trimmed();
//  qDebug() << "FTP-answer" << answer;
  m__Socket->disconnect();

  emit ftpAnswer( QVariant( answer ).toString() );

  if ( !checkCode( answer, 331 ) ) return;

  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAuthPassReply()) );

  executeCommand( tr( "pass %1\n" ).arg( m__Password ) );
}

void FTPEngine::socketAuthPassReply()
{
  QByteArray answer = m__Socket->readAll().trimmed();
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
  answer = answer.trimmed();
  m__Socket->disconnect();

  int code = ftpAnswerCode( answer );
  QString text = ftpAnswerText( answer );
  bool sendAnswer = false;
  bool result = false;
  bool sendNextCommand = true;

  m__LastText = text;

//  qDebug() << "FTP-answer" << answer;
  if ( m__ActualCommand != NULL )
    switch ( m__ActualCommand->type() )
    {
    case FTPCommand::Type_Noop:
      result = ( code == 200 || code == 226 );
      if ( !result ) m__LastError = text;
      else
      {
        m__LastText = text;
        if ( code == 226 ) m__LastText = m__LastText.mid( 0, m__LastText.indexOf( "200" )-1 ).trimmed();
      }
      sendAnswer = ( m__ActualCommand == m__CurrentCommand ||
                     m__CurrentCommand->type() == FTPCommand::Type_List ||
                     m__CurrentCommand->type() == FTPCommand::Type_Retr ||
                     m__CurrentCommand->type() == FTPCommand::Type_Stor || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Help:
      result = ( code == 331 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_User:
      result = ( code == 331 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Pass:
      result = ( code == 230 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Type:
      result = ( code == 200 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Pwd:
      result = ( code == 257 );
      if ( !result ) m__LastError = text;
      else m__LastText = text.split( "\"" ).at( 1 );
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Cdup:
      result = ( code == 250 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Cwd:
      result = ( code == 250 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_List:
      result = ( code == 150 );
      if ( !result ) m__LastError = text;
      else
      {
          m__LastText = text;
          m__Transfer->setBuffer( m__CommandIODevice[m__CurrentCommand].second );
      }
      sendAnswer = ( m__ActualCommand == m__CurrentCommand &&
                     m__PendingCommands.isEmpty() || !result );
      sendNextCommand = sendAnswer;
      break;
    case FTPCommand::Type_Mkd:
      result = ( code == 257 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Rmd:
      result = ( code == 250 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Allo:
      result = ( code == 200 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Size:
      result = ( code == 213 );
      if ( !result ) m__LastError = text;
      else
      {
        m__LastText = text;

        QString fileName = m__CurrentCommand->argument();
        fileName = fileName.replace( "\"", "" );
        qint64 fileSize = m__LastText.toInt();
        m__CommandIODevice[m__CurrentCommand].first->setFileName( fileName );
        m__CommandIODevice[m__CurrentCommand].first->setSize( fileSize );
      }
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Retr:
      result = ( code == 150 );
      if ( !result ) m__LastError = text;
      else
      {
          m__LastText = text;
          m__Transfer->setBuffer( m__CommandIODevice[m__CurrentCommand].second );
      }
      sendAnswer = ( m__ActualCommand == m__CurrentCommand &&
                     m__PendingCommands.isEmpty() || !result );
      sendNextCommand = sendAnswer;
      break;
    case FTPCommand::Type_Stor:
      result = ( code == 150 );
      if ( !result ) m__LastError = text;
      else
      {
        m__LastText = text;

        m__Transfer->setBuffer( m__CommandIODevice[m__CurrentCommand].second );
        m__Transfer->startUploading();

      }

      sendAnswer = ( m__ActualCommand == m__CurrentCommand &&
                     m__PendingCommands.isEmpty() || !result );
      sendNextCommand = sendAnswer;
      break;
    case FTPCommand::Type_Dele:
      result = ( code == 250 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Port:
      result = ( code == 200 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    case FTPCommand::Type_Quit:
      result = ( code == 200 );
      if ( !result ) m__LastError = text;
      else m__LastText = text;
      sendAnswer = ( m__ActualCommand == m__CurrentCommand || !result );
      sendNextCommand = !sendAnswer;
      break;
    }

  emit ftpAnswer( tr( "%1 %2" ).arg( code ).arg( m__LastText ) );

  if ( m__ActualCommand != NULL )
  {
    if ( !result ) clearPendingCommands();
    if ( sendAnswer ) sendAnswerResult( result );
    if ( sendNextCommand )
    {
      delete m__ActualCommand;
      m__ActualCommand = NULL;
      nextCommand();
    }
  }
}

void FTPEngine::nextCommand()
{
  if ( m__PendingCommands.isEmpty() || m__ActualCommand != NULL ) return;

  m__ActualCommand = m__PendingCommands.takeFirst();
  if ( !m__ActualCommand->isAutomatically() ) m__CurrentCommand = m__ActualCommand;
  int idx = 0;
  while ( m__CurrentCommand == NULL && idx < m__PendingCommands.count() )
  {
    if ( !m__PendingCommands.at( idx )->isAutomatically() )
      m__CurrentCommand = m__PendingCommands.at( idx );
    idx++;
  }

  m__LastError = QString();
  m__LastText = QString();
  connect( m__Socket, SIGNAL(readyRead()), this, SLOT(socketAllReply()) );
  executeCommand( QString( "%1 %2\r\n" ).arg(
                    m__ActualCommand->name().toUpper(), m__ActualCommand->argument() ) );
}

void FTPEngine::transferDataProgress( qint64 currentSize, qint64 overallSize )
{
  if ( m__CurrentCommand->type() == FTPCommand::Type_Retr )
    emit loadProgress( m__CommandIODevice.value( m__CurrentCommand ).first->fileName(),
                       m__CommandIODevice.value( m__CurrentCommand ).second->size(),
                       m__CommandIODevice.value( m__CurrentCommand ).first->size() );
  else if ( m__CurrentCommand->type() == FTPCommand::Type_Stor )
      emit loadProgress( m__CommandIODevice.value( m__CurrentCommand ).first->fileName(),
                         currentSize, overallSize );
}

void FTPEngine::transferDataFinished()
{
    if ( m__CurrentCommand == NULL ) return;


  if ( m__CurrentCommand->type() == FTPCommand::Type_List )
  {
    m__CommandIODevice[m__CurrentCommand].second->close();

    m__DirData = m__DirData.trimmed();
    foreach ( QByteArray line, m__DirData.split( '\n' ) )
    {
      line = line.replace( "\r", "" );
      m__DirInfo << new FileInfo();
      parseDir( line, m__User, m__DirInfo.last() );
    }
    m__DirData.clear();
    delete m__CommandIODevice[m__CurrentCommand].second;
  }
  if ( m__CommandIODevice[m__CurrentCommand].first != NULL )
      delete m__CommandIODevice[m__CurrentCommand].first;
  m__CommandIODevice.remove( m__CurrentCommand );

  m__ActualCommand = NULL;
  m__Timer->singleShot( 500, this, SLOT(nextCommand()) );
}
