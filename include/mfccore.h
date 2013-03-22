#ifndef MFCCORE_H
#define MFCCORE_H

#include <QAbstractItemModel>
#include <QDateTime>
#include <QAuthenticator>


#ifdef MFCCORE_LIBRARY
#define MFCCORE_EXPORT Q_DECL_EXPORT
#else
#define MFCCORE_EXPORT Q_DECL_IMPORT
#endif


class QSettings;

typedef struct
{
  QString surname;
  QString firstname;
  QString lastname;
} StructName;

class MFCCORE_EXPORT MFCCore : public QObject
{
  Q_OBJECT

public:
  enum Period {Undefined = 0, Random, Daily, Weekly, Monthly, Quarterly, Semiannual, Yearly};

  static const QStringList byteSizeNames;

  static QString periodName( Period period );
  static Period period( QString name );

  static bool matches( const QString &arg1, const QString &arg2, Qt::MatchFlag flag = Qt::MatchExactly );

  static int findColumn( QAbstractItemModel *model, const QString &name );
  static QList<QModelIndex> findIndexes( QAbstractItemModel *model, QString value,
                                         int column = 0, Qt::MatchFlag flag = Qt::MatchExactly );

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

  static QString humanBytes( qint64 size );

  static QSettings * appSettings( QString fileName );
  static QSettings * appSettings();

  static QAuthenticator * authenticator( QString key );
  static void removeAuthenticator( QString key );


private:
  static MFCCore *m__Core;
  static QSettings *m__Settings;
  static QHash<QString, QAuthenticator> m__Authenticators;

  explicit MFCCore();


private slots:
  void settingsDestroyed();
};

#endif // MFCCORE_H
