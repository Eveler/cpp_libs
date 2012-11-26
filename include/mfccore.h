#ifndef MFCCORE_H
#define MFCCORE_H

#include <QAbstractItemModel>

class MFCCore
{
public:
  static int findColumn( QAbstractItemModel *model, const QString &name );

  template<class T>
  static QList<T> exists( QList<T> list1, QList<T> list2 )
  {
    QList<T> result = QList<T>();
    foreach ( T val, list2 )
      if ( list1.contains( val ) )
        result << val;

    return result;
  }

  template<class T>
  static QList<T> notExists( QList<T> list1, QList<T> list2 )
  {
    QList<T> result = list1;
    foreach ( T val, list2 ) result.removeOne( val );

    return result;
  }

};

#endif // MFCCORE_H
