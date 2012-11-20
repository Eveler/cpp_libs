#include "mfccore.h"

#include <QStringList>

int MFCCore::findColumn( QAbstractItemModel *model, const QString &name )
{
  if ( model == NULL ) return -1;

  for ( int cIdx = 0; cIdx < model->columnCount(); cIdx++ )
    if ( model->headerData( cIdx, Qt::Horizontal ).toString() == name )
      return cIdx;

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

template<class T>
MFCCORE_EXPORT QList<T> MFCCore::exists( QList<T> list1, QList<T> list2 )
{
  QList<T> result = QList<T>();
  foreach ( T val, list2 )
    if ( list1.contains( val ) )
      result << val;

  return result;
}

template<class T>
MFCCORE_EXPORT QList<T> MFCCore::notExists( QList<T> list1, QList<T> list2 )
{
  QList<T> result = list1;
  foreach ( T val, list2 ) result.removeOne( val );

  return result;
}
