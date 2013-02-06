#include "mfccore.h"

QString MFCCore::periodName( Period period )
{
  if ( period == Daily ) return QObject::tr( "Ежедневный" );
  if ( period == Weekly ) return QObject::tr( "Еженедельный" );
  if ( period == Monthly ) return QObject::tr( "Ежемесячный" );
  if ( period == Quarterly ) return QObject::tr( "Квартальный" );
  if ( period == Semiannual ) return QObject::tr( "Полугодовой" );
  if ( period == Yearly ) return QObject::tr( "Годовой" );
  return QObject::tr( "Undefined" );
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
                                           Qt::MatchFlag flag, int column )
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
