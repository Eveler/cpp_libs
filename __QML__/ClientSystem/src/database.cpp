#include "database.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


Database::Database(QObject *parent) :
  QObject(parent)
{
}

Database::~Database()
{
}

QString Database::lastError() const
{
  return m__LastError;
}

QString Database::connectionName()
{
  if ( m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return m__ConnectionName;
}

bool Database::setConnectionName( QString connectionName )
{
  if ( !QSqlDatabase::contains( connectionName ) )
  {
    QString connection = this->connectionName();
    if ( connection.isEmpty() ) return false;
  }
  else
  {
    m__ConnectionName = connectionName;
    emit connectionNameChanged();
  }
  return true;
}

QDateTime Database::serverTime()
{
  QSqlDatabase db = QSqlDatabase::database( connectionName(), false );
  db.open();
  if ( !db.isValid() )
  {
    emit receivedError( tr( "Database with name [%1] is not valid." ).arg( db.connectionName() ) );
    return QDateTime();
  }
  if ( db.lastError().isValid() )
  {
    emit receivedError( tr( "Database error:\n%1" ).arg( db.lastError().text() ) );
    return QDateTime();
  }
  if ( !db.isOpen() )
  {
    emit receivedError( tr( "Database open error." ) );
    return QDateTime();
  }
  QSqlQuery qry( db );
  if ( !qry.exec( tr( "SELECT now()" ) ) )
  {
    emit receivedError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return QDateTime();
  }
  qry.next();
  return qry.record().value( 0 ).toDateTime();
}

void Database::receivedError( QString errorText )
{
  m__LastError = errorText;
  emit lastErrorChanged();
}
