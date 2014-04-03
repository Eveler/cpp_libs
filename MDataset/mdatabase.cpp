#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>


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

void MDatabase::createDatabase( const QString &driverName, const QString &connectionName, const QString &hostName, int port,
                                const QString &databaseName, const QString &userName, const QString &password )
{
  if ( !QSqlDatabase::isDriverAvailable( driverName ) || QSqlDatabase::connectionNames().contains( connectionName ) ) return;

  QSqlDatabase database = QSqlDatabase::addDatabase( driverName, connectionName );
  database.setHostName( hostName );
  database.setPort( port );
  database.setDatabaseName( databaseName );
  database.setUserName( userName );
  database.setPassword( password );
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
