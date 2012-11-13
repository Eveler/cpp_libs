#ifndef PROPERTIESSQLWORKER_H
#define PROPERTIESSQLWORKER_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include "storageitemmodel.h"
#include "pgdb.h"
#include <QSqlDriver>

class SqlResult
{
public:
  SqlResult( QSqlError error, QSqlQuery *query );
  ~SqlResult();

  QSqlError sqlError() const;
  QSqlQuery * sqlQuery() const;

private:
  QSqlError m_SqlError;
  QSqlQuery *m_SqlQuery;
};

class PropertiesSqlWorker
{
public:
  static PropertiesSqlWorker & instance( QString alias, QSqlDatabase &db );
  static void remove( QString alias );

  static QString preparePsName( const QString &ps_Name );

  const QString &alias() const;

  bool isValid();

  QSqlDatabase database() const;

  Properties * prepareProperties( QString ps_Name );
  SqlResult * loadProperties( Properties *properties );
  SqlResult * load( Properties *properties,
                    QString filter = QString(), QString order = QString() );
  SqlResult * notExists( Properties *properties, QStringList exists, const QString &keyField );
  SqlResult * nextVal( Properties *properties );
  SqlResult * nextVal( QString sequenceName );

  bool transaction();
  bool commit();
  bool rollback();

  QSqlError saveRecord( MFCRecord *record, bool isNew, bool firstAsPrimaryOnAdd = true );
  QSqlError saveChanges( MFCRecord *record );

  bool isInTransaction();

private:
  static QHash<QString, PropertiesSqlWorker *> m_PSW;
  static PropertiesSqlWorker *null_PSW;
  QString *m_Alias;
  QSqlDatabase m_DB;
  PgDB *m_PgDB;

  PropertiesSqlWorker();
  PropertiesSqlWorker( QString alias, QSqlDatabase &db );
  ~PropertiesSqlWorker();

  QList<QPair<MFCRecord *, bool> > recordsInTransaction;

  bool m_InTransaction;
};

#endif // PROPERTIESSQLWORKER_H
