#include "mfccore.h"

#include <QStringList>

int MFCCore::findColumn( QAbstractItemModel *model, const QString &name )
{
  if ( model == NULL ) return -1;

  for ( int cIdx = 0; cIdx < model->columnCount(); cIdx++ )
    if ( model->headerData( cIdx, Qt::Horizontal ).toString() == name )
      return cIdx;

  QList<QVariant> vals1 = QList<QVariant>() << 1 << 3 << 5;
  QList<QVariant> vals2 = QList<QVariant>() << 1 << 2 << 5;
  QList<QVariant> vals3 = MFCCore::notExists( vals1, vals2 );

  QStringList vals4 = QStringList() << "1" << "3" << "5";
  QStringList vals5 = QStringList() << "1" << "2" << "5";
  QStringList vals6 = MFCCore::notExists( vals4, vals5 );
  vals6 = MFCCore::exists( vals4, vals5 );

  return -1;
}

//QList<QVariant> MFCCore::exists( QList<QVariant> list1, QList<QVariant> list2 )
//{
//  QList<QVariant> result = QList<QVariant>();
//  foreach ( QVariant val, list2 )
//    if ( list1.contains( val ) )
//      result << val;

//  return result;
//}

//QList<QVariant> MFCCore::notExists( QList<QVariant> list1, QList<QVariant> list2 )
//{
//  QList<QVariant> result = list1;
//  foreach ( QVariant val, list2 ) result.removeOne( val );

//  return result;
//}
