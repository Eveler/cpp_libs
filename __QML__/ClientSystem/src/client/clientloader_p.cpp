#include "clientloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void ClientLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, clid, isorg"
                      " FROM clientlist%1 ORDER BY clname" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    ClientInfo *info = new ClientInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    if ( qry.record().value( tr( "isorg" ) ).toInt() == 1 )
    {
      info->setOrganisationIdentifier( qry.record().value( tr( "clid" ) ).toString() );
      info->setHumanIdentifier( QVariant() );
    }
    else
    {
      info->setOrganisationIdentifier( QVariant() );
      info->setHumanIdentifier( qry.record().value( tr( "clid" ) ).toString() );
    }
    emit sendInfo( info );
  }
}

ClientLoader_P::ClientLoader_P( ClientLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

ClientLoader_P::~ClientLoader_P()
{
}

ClientLoader * ClientLoader_P::p_dptr() const
{
  return qobject_cast<ClientLoader *>( parent() );
}
