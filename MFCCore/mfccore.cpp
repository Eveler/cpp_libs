#include "mfccore.h"

#include "math.h"
#include "mucalculator.h"

#include <QStringList>
#include <QSettings>


MFCCore *MFCCore::m__Core = NULL;
QSettings *MFCCore::m__Settings = NULL;
QHash<QString, QAuthenticator> MFCCore::m__Authenticators = QHash<QString, QAuthenticator>();

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

MFCCore::Period MFCCore::period( QString name )
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

int MFCCore::findColumn( QAbstractItemModel *model, const QString &name )
{
  if ( model == NULL ) return -1;

  for ( int cIdx = 0; cIdx < model->columnCount(); cIdx++ )
    if ( model->headerData( cIdx, Qt::Horizontal ).toString() == name )
      return cIdx;

  return -1;
}

QList<QModelIndex> MFCCore::findIndexes( QAbstractItemModel *model, QString value,
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

QDate MFCCore::addDays(const QDate &date, const int &days, bool isOverall, QList<int> weekend )
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

QSettings * MFCCore::appSettings( QString fileName )
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

QAuthenticator * MFCCore::authenticator( QString key )
{
  if ( !m__Authenticators.contains( key ) )
    m__Authenticators[key] = QAuthenticator();

  return &m__Authenticators[key];
}

void MFCCore::removeAuthenticator( QString key )
{
  if ( !m__Authenticators.contains( key ) ) return;

  m__Authenticators.remove( key );
}

MFCCore::MFCCore() {}

void MFCCore::settingsDestroyed()
{
  m__Settings = NULL;
}
