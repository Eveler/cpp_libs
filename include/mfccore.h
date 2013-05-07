#ifndef MFCCORE_H
#define MFCCORE_H

#include "export/mfccore_export_lib.h"

#include <QAbstractItemModel>
#include <QDateTime>
#include <QAuthenticator>
#include <QProcess>
#include <QFile>


class QSettings;

typedef struct
{
  QString surname;
  QString firstname;
  QString lastname;
} StructName;

class EXPORT_MFCCORE MFCCore : public QObject
{
  Q_OBJECT

public:
  enum Period {Undefined = 0, Random, Daily, Weekly, Monthly, Quarterly, Semiannual, Yearly};

  static const QStringList byteSizeNames;

  static QString periodName( Period period );
  static Period period( const QString &name );

  static bool matches( const QString &arg1, const QString &arg2, Qt::MatchFlag flag = Qt::MatchExactly );

  static int findColumn(const QAbstractItemModel *model, const QString &name );
  static QList<QModelIndex> findIndexes( QAbstractItemModel *model, const QString &value,
                                         int column = 0, Qt::MatchFlag flag = Qt::MatchExactly );

  template<class T>
  static QList<T> exists( const QList<T> &list1, const QList<T> &list2 )
  {
    QList<T> result = QList<T>();
    foreach ( T val, list2 )
      if ( list1.contains( val ) )
        result << val;

    return result;
  }

  template<class T>
  static QList<T> notExists( const QList<T> &list1, const QList<T> &list2 )
  {
    QList<T> result = list1;
    foreach ( T val, list2 ) result.removeOne( val );

    return result;
  }

  static QDate addDays( const QDate &date, const int &days, bool isOverall = true,
                        const QList<int> &weekend = QList<int>() << 6 << 7 );

  static QString humanBytes( qint64 size );

  static QSettings * appSettings( const QString &fileName );
  static QSettings * appSettings();

  static QAuthenticator * authenticator( const QString &key );
  static void removeAuthenticator( const QString &key );
  static bool authenticatorExists( const QString &key );

  static QString execFile(const QString &fName, const bool block_ui=true);
  static QString execFile(const QByteArray &buf, const QString &extension,
                          const bool block_ui=true);
  static QString execFile(const QString &buf, const QString extension,
                          const bool block_ui=true) {
    return execFile(buf.toLocal8Bit(),extension,block_ui);
  }

#if QT_VERSION >= 0x050000
  /** Создание архива с именем archiveName. В archivePath содержится путь к файлу архива.
  Функция архивирует файл или директорию указанную в filePath*/
  static bool zip( const QString &archiveName, const QString &filePath,
                   const QString &archivePath = QString() );
  /** Создание архива с именем archiveName. В archivePath содержится путь к файлу архива.
  Функция архивирует файл или директорию указанную в filePath*/
  static bool unzip( const QString &archiveName, const QString &unzipPath = QString() );
#endif

private:
  static MFCCore *m__Core;
  static QSettings *m__Settings;
  static QHash<QString, QAuthenticator> m__Authenticators;
  static QProcess *ext_proc;
  static QFile *ext_proc_file;

  explicit MFCCore();


private slots:
  void settingsDestroyed();
  void processFinished(int exitCode);
  void processError(QProcess::ProcessError err);
};

#endif // MFCCORE_H
