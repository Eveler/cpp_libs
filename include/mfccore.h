#ifndef MFCCORE_H
#define MFCCORE_H

#if defined(MFCCORE_LIBRARY)
#  define MFCCORE_EXPORT Q_DECL_EXPORT
#else
#  define MFCCORE_EXPORT Q_DECL_IMPORT
#endif

#include <QAbstractItemModel>

class MFCCore
{
public:
  static int findColumn( QAbstractItemModel *model, const QString &name );
//  static QList<QVariant> exists( QList<QVariant> list1, QList<QVariant> list2 );
//  static QList<QVariant> notExists( QList<QVariant> list1, QList<QVariant> list2 );
  template<class T>
  MFCCORE_EXPORT static QList<T> exists( QList<T> list1, QList<T> list2 );
  template<class T>
  MFCCORE_EXPORT static QList<T> notExists( QList<T> list1, QList<T> list2 );
};

#endif // MFCCORE_H
