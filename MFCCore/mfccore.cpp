#include "mfccore.h"

#include "math.h"
#include "mucalculator.h"

#include <QStringList>
#include <QSettings>
#include <QUuid>
#include <QDir>

#include "amslogger.h"

MFCCore *MFCCore::m__Core = NULL;
QSettings *MFCCore::m__Settings = NULL;
QHash<QString, QAuthenticator> MFCCore::m__Authenticators = QHash<QString, QAuthenticator>();
QProcess *MFCCore::ext_proc=NULL;
QFile *MFCCore::ext_proc_file=NULL;

const QStringList MFCCore::byteSizeNames = QStringList()
    << QObject::tr( "Б" ) << QObject::tr( "КБ" ) << QObject::tr( "МБ" )
    << QObject::tr( "ГБ" ) << QObject::tr( "ТБ" ) << QObject::tr( "ПБ" )
    << QObject::tr( "ЭБ" ) << QObject::tr( "ЗБ" ) << QObject::tr( "ЙБ" );

QString MFCCore::periodName( Period period )
{
  if ( period == Random ) return QObject::tr( "Произвольный" );
  else if ( period == Daily ) return QObject::tr( "Ежедневный" );
  else if ( period == Weekly ) return QObject::tr( "Еженедельный" );
  else if ( period == Monthly ) return QObject::tr( "Ежемесячный" );
  else if ( period == Quarterly ) return QObject::tr( "Квартальный" );
  else if ( period == Semiannual ) return QObject::tr( "Полугодовой" );
  else if ( period == Yearly ) return QObject::tr( "Годовой" );
  else return QObject::tr( "Undefined" );
}

MFCCore::Period MFCCore::period( const QString &name )
{
  if ( name == QObject::tr( "Произвольный" ) ) return Random;
  else if ( name == QObject::tr( "Ежедневный" ) ) return Daily;
  else if ( name == QObject::tr( "Еженедельный" ) ) return Weekly;
  else if ( name == QObject::tr( "Ежемесячный" ) ) return Monthly;
  else if ( name == QObject::tr( "Квартальный" ) ) return Quarterly;
  else if ( name == QObject::tr( "Полугодовой" ) ) return Semiannual;
  else if ( name == QObject::tr( "Годовой" ) ) return Yearly;
  else return Undefined;
}

bool MFCCore::matches( const QString &arg1, const QString &arg2, Qt::MatchFlag flag )
{
  if ( flag == Qt::MatchStartsWith )
    return arg1.startsWith( arg2 );
  else if ( flag == Qt::MatchEndsWith )
    return arg1.endsWith( arg2 );
  else if ( flag == Qt::MatchContains )
    return arg1.contains( arg2 );
  else return ( arg1 == arg2 );
}

int MFCCore::findColumn( const QAbstractItemModel *model, const QString &name )
{
  if ( model == NULL ) return -1;

  for ( int cIdx = 0; cIdx < model->columnCount(); cIdx++ )
    if ( model->headerData( cIdx, Qt::Horizontal ).toString() == name )
      return cIdx;

  return -1;
}

QList<QModelIndex> MFCCore::findIndexes( QAbstractItemModel *model, const QString &value,
                                         int column, Qt::MatchFlag flag )
{
  QList<QModelIndex> result = QList<QModelIndex>();

  if ( model != NULL )
    for ( int rIdx = 0; rIdx < model->rowCount(); rIdx++ )
    {
      QVariant val = model->index( rIdx, column ).data();
      if ( val.type() == QVariant::Int &&
           matches( QString::number( val.toInt() ), value, flag ) )
        result << model->index( rIdx, column );
      else if ( val.type() == QVariant::Double &&
                matches( QString::number( val.toDouble() ), value, flag ) )
        result << model->index( rIdx, column );
      else if ( matches( val.toString(), value, flag ) )
        result << model->index( rIdx, column );
    }

  return result;
}

QDate MFCCore::addDays( const QDate &date, const int &days, bool isOverall, const QList<int> &weekend )
{
  QMap<int, int> weekdays;
  foreach( int dayNum, weekend )
    if ( dayNum > 7 ) return QDate();
    else weekdays.insert( dayNum, dayNum );
  if ( weekdays.count() == 7 ) return QDate();

  QDate result = date;
  if ( days == 0 ) return result;

  if ( isOverall )
  {
    int udays = ( days > 0 ? 1 : -1 )*days;
//    DPRINT( udays, qApp );
    for ( int i = 0; i < udays; i++ )
    {
      result = result.addDays( ( days > 0 ? 1 : -1 ) );
      if ( days > 0 )
        while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
    }
    if ( days < 0 )
      while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
  }
  else
  {
    result = result.addDays( days );
    while ( weekend.contains( result.dayOfWeek() ) ) result = result.addDays( 1 );
  }
  return result;
}

QString MFCCore::humanBytes( qint64 size )
{
  if ( size == 0 ) return QObject::tr( "0 Б" );

  int idx = floor( log( size )/log(1024) );
  double rounded = muCalculator::round( ((double)size/pow( 1024., (double)idx )), 2 );
  return QString( QString::number( rounded )+" "+byteSizeNames[idx] );
}

QSettings * MFCCore::appSettings( const QString &fileName )
{
  if ( m__Core == NULL ) m__Core = new MFCCore;

  if ( m__Settings == NULL )
  {
    m__Settings = new QSettings( fileName, QSettings::IniFormat );
    connect( m__Settings, SIGNAL(destroyed()), m__Core, SLOT(settingsDestroyed()) );
  }
  if ( m__Settings->fileName().endsWith( fileName ) ) return m__Settings;
  else return NULL;
}

QSettings * MFCCore::appSettings()
{
  return m__Settings;
}

QAuthenticator * MFCCore::authenticator( const QString &key )
{
  if ( !m__Authenticators.contains( key ) )
    m__Authenticators[key] = QAuthenticator();

  return &m__Authenticators[key];
}

void MFCCore::removeAuthenticator( const QString &key )
{
  if ( !m__Authenticators.contains( key ) ) return;

  m__Authenticators.remove( key );
}

bool MFCCore::authenticatorExists( const QString &key )
{
  return m__Authenticators.contains( key );
}

QString MFCCore::execFile(const QString &fName, const bool block_ui){
  LogDebug()<<tr("About to execute \"%1\"").arg(fName);
  if(!m__Core && !block_ui) m__Core=new MFCCore;
  if(!ext_proc){
    ext_proc=new QProcess(m__Core);
    ext_proc->setProcessChannelMode(QProcess::MergedChannels);
    if(!block_ui){
      connect(ext_proc,SIGNAL(finished(int)),m__Core,SLOT(processFinished(int)));
      connect(ext_proc,SIGNAL(error(QProcess::ProcessError)),
              m__Core,SLOT(processError(QProcess::ProcessError)));
    }
  }
  QString errStr;

  QString fileName=fName;
  if(block_ui){
#ifdef Q_OS_WIN
    fileName.replace("/","\\");
    int res=ext_proc->execute(tr("cmd /C \"%1\"").arg(fileName));
#else
    int res=ext_proc->execute(tr("xdg-open \"%1\"").arg(fileName));
#endif
    if(res==-2){
      errStr=tr("Нет возможности запустить дочерний процесс: %1: %2")
               .arg(fileName).arg(ext_proc->errorString());
    }else if(res==-1){
      errStr=tr("Дочерний процесс внезапно (o_O) завершился: %1: %2")
               .arg(fileName).arg(ext_proc->errorString());
    }else if(!ext_proc->errorString().isEmpty() &&
             ext_proc->errorString()!="Unknown error")
      errStr=tr("Дочерний процесс вернул ошибку: %1").arg(ext_proc->errorString());
    QString sys_out=ext_proc->readAllStandardOutput()+" "+
        ext_proc->readAllStandardError();
    if(sys_out.simplified().length()>0)
      errStr+=tr("Вывод процесса: %1").arg(sys_out);

    ext_proc->deleteLater();
    ext_proc=NULL;
    if(ext_proc_file){
      ext_proc_file->remove();
      ext_proc_file->deleteLater();
      ext_proc_file=NULL;
    }
    return errStr;
  }else{
#ifdef Q_OS_WIN
    fileName.replace("/","\\");
    ext_proc->start(tr("cmd /C %1").arg(fileName));
#else
    ext_proc->start(tr("xdg-open %1").arg(fileName));
#endif
    if(!ext_proc->waitForStarted()){
      errStr=tr("Истекло время ожидания запуска процесса: %1")
          .arg(ext_proc->errorString());
      ext_proc->deleteLater();
      ext_proc=NULL;
    }
  }

  return errStr;
}

QString MFCCore::execFile(const QByteArray &buf, const QString &extension,
                          const bool block_ui){
  QUuid uuid=QUuid::createUuid();
  QString fileName=uuid.toString();
  fileName=QDir::tempPath()+tr("/exec%1.%2").arg(
        fileName.mid(1,fileName.length()-2)).arg(extension);
  if(!m__Core && !block_ui) m__Core=new MFCCore;
  QString errStr;

  if(!ext_proc_file){
    ext_proc_file=new QFile(fileName,m__Core);
  }else{
    return tr("Файл \"%1\" уже открыт").arg(ext_proc_file->fileName());
  }

  if(!ext_proc_file->open(QFile::WriteOnly)){
    errStr=tr("Ошибка создания временного файла: %1: %2")
        .arg(fileName).arg(ext_proc_file->errorString());
    ext_proc_file->deleteLater();
    ext_proc_file=NULL;
    return errStr;
  }
  ext_proc_file->write(buf);
  if(ext_proc_file->error()!=QFile::NoError){
    errStr=tr("Ошибка записи данных во временный файл: %1").arg(
          ext_proc_file->errorString());
    ext_proc_file->close();
    ext_proc_file->remove();
    ext_proc_file->deleteLater();
    ext_proc_file=NULL;
    return errStr;
  }
  ext_proc_file->close();

  return execFile(fileName,block_ui);
}

MFCCore::MFCCore() {}

void MFCCore::settingsDestroyed()
{
  m__Settings = NULL;
}

void MFCCore::processFinished(int exitCode){
  if(!ext_proc) return;

  QString errStr;
  if(exitCode==-2){
    errStr=tr("Нет возможности запустить дочерний процесс: %1")
             .arg(ext_proc->errorString());
  }else if(exitCode==-1){
    errStr=tr("Дочерний процесс внезапно завершился: %1")
             .arg(ext_proc->errorString());
  }else if(!ext_proc->errorString().isEmpty() &&
           ext_proc->errorString()!="Unknown error")
    errStr=tr("Дочерний процесс вернул ошибку: %1").arg(ext_proc->errorString());
  QString sys_out=ext_proc->readAllStandardOutput()+" "+
      ext_proc->readAllStandardError();
  if(sys_out.simplified().length()>0)
    errStr+=tr("Вывод процесса: %1").arg(sys_out);

  ext_proc->deleteLater();
  ext_proc=NULL;

  if(ext_proc_file){
    ext_proc_file->remove();
    ext_proc_file->deleteLater();
    ext_proc_file=NULL;
  }
}

void MFCCore::processError(QProcess::ProcessError err){
  if(err==QProcess::FailedToStart || err==QProcess::Crashed ||
     err==QProcess::Timedout || err==QProcess::UnknownError){
    if(ext_proc){
      ext_proc->deleteLater();
      ext_proc=NULL;

      if(ext_proc_file){
        ext_proc_file->remove();
        ext_proc_file->deleteLater();
        ext_proc_file=NULL;
      }
    }
  }
}
