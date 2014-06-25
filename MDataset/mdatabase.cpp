#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "amslogger.h"


MDatabase *MDatabase::m__Instance = NULL;

MDatabase::~MDatabase()
{
//  m__Locker->lockForWrite();
  foreach ( QString connectionName, QSqlDatabase::connectionNames() )
  {
    {
      QSqlDatabase database = QSqlDatabase::database( connectionName, false );
      database.close();
    }
    QSqlDatabase::removeDatabase( connectionName );
  }
//  m__Locker->unlock();
  delete m__Locker;
  m__Locker = NULL;
}

MDatabase * MDatabase::instance( QObject *parent )
{
  if ( m__Instance == NULL ) m__Instance = new MDatabase( parent );

  return m__Instance;
}

bool MDatabase::createDatabase( const QString &driverName, const QString &connectionName, const QString &hostName, int port,
                                const QString &databaseName, const QString &userName, const QString &password )
{
  LogDebug() << "<<= Try create database connection =>>";
  if ( QSqlDatabase::connectionNames().contains( connectionName ) )
  {
    LogDebug() << "Connection" << connectionName << "already exists.";
    return false;
  }

  QSqlDatabase database = QSqlDatabase::addDatabase( driverName, connectionName );
  database.setHostName( hostName );
  database.setPort( port );
  database.setDatabaseName( databaseName );
  database.setUserName( userName );
  database.setPassword( password );

  bool result = database.open();
  if ( !result )
  {
    QSqlDatabase::removeDatabase( connectionName );
    LogDebug() << QSqlDatabase::drivers();
    LogDebug() << database.lastError().text();
  }
  return result;
}

QSqlQuery * MDatabase::getQuery( const QString &queryText, const QString &connectionName )
{
  m__Locker->lockForWrite();
  QSqlDatabase database = QSqlDatabase::database( connectionName, false );
  database.open();
  QSqlQuery *result = new QSqlQuery( queryText, database );
  m__Locker->unlock();
  return result;
}

MDatabase::MDatabase( QObject *parent ) :
  QObject(parent),
  m__Locker(new QReadWriteLock)
{

}
