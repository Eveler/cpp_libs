#include "mfccore.h"

int MFCCore::findColumn( QAbstractItemModel *model, const QString &name )
{
  if ( model == NULL ) return -1;

  for ( int cIdx = 0; cIdx < model->columnCount(); cIdx++ )
    if ( model->headerData( cIdx, Qt::Horizontal ).toString() == name )
      return cIdx;

  return -1;
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
