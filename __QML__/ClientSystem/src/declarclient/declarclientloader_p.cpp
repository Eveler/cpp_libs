#include "declarclientloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void DeclarClientLoader_P::run()
{
  m__Successfully = true;
  QSqlDatabase db = QSqlDatabase::database( p_dptr()->connectionName(), false );
  db.open();
  if ( !db.isValid() )
  {
    m__Successfully = false;
    emit sendError( tr( "Database with name [%1] is not valid." ).arg( db.connectionName() ) );
    return;
  }
  if ( db.lastError().isValid() )
  {
    m__Successfully = false;
    emit sendError( tr( "Database error:\n%1" ).arg( db.lastError().text() ) );
    return;
  }
  if ( !db.isOpen() )
  {
    m__Successfully = false;
    emit sendError( tr( "Database open error." ) );
    return;
  }
  QSqlQuery qry( db );
  if ( !qry.exec( tr( "SELECT id AS identifier, declar_id AS declarIdentifier,"
                      " client_id AS clientIdentifier"
                      " FROM declar_clients%1 ORDER BY declar_id, client_id" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    DeclarClientInfo *info = new DeclarClientInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setDeclarIdentifier( qry.record().value( tr( "declarIdentifier" ) ) );
    info->setClientIdentifier( qry.record().value( tr( "clientIdentifier" ) ) );
    emit sendInfo( info );
  }
}

DeclarClientLoader_P::DeclarClientLoader_P( DeclarClientLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

DeclarClientLoader_P::~DeclarClientLoader_P()
{
}

DeclarClientLoader * DeclarClientLoader_P::p_dptr() const
{
  return qobject_cast<DeclarClientLoader *>( parent() );
}
