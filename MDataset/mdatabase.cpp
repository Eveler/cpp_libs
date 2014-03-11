#include "mdatabase.h"

#include <QSqlDatabase>

#include <QDebug>


MDatabase::MDatabase( QObject *parent ) : QObject(parent) {}

MDatabase::~MDatabase()
{
  foreach ( QString connectionName, QSqlDatabase::connectionNames() )
  {
    {
      QSqlDatabase database = QSqlDatabase::database( connectionName, false );
      database.close();
    }
    QSqlDatabase::removeDatabase( connectionName );
  }
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
