#ifndef MFCCORE_H
#define MFCCORE_H

#include <QAbstractItemModel>
#include <QDateTime>

#ifdef MFCCORE_LIBRARY
#define MFCCORE_EXPORT Q_DECL_EXPORT
#else
#define MFCCORE_EXPORT Q_DECL_IMPORT
#endif

typedef struct
{
  QString surname;
  QString firstname;
  QString lastname;
} StructName;

class MFCCORE_EXPORT MFCCore
{
public:
  enum Period {Undefined = 0, Daily, Weekly, Monthly, Quarterly, Semiannual, Yearly};

  static QString periodName( Period period );
  static Period period( QString name );

  static bool matches( const QString &arg1, const QString &arg2, Qt::MatchFlag flag = Qt::MatchExactly );

  static int findColumn( QAbstractItemModel *model, const QString &name );
  static QList<QModelIndex> findIndexes( QAbstractItemModel *model, QString value,
                                         Qt::MatchFlag flag = Qt::MatchExactly, int column = 0 );

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

  static QDate addDays( const QDate &date, const int &days, bool isOverall = true,
                        QList<int> weekend = QList<int>() << 6 << 7 );

};

#endif // MFCCORE_H
