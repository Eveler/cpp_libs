#include "organisationloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void OrganisationLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, fullname, human_id AS humanIdentifier,"
                      " addr AS address, phone, \"e-mail\" AS email"
                      " FROM orgs%1 ORDER BY fullname" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    OrganisationInfo *info = new OrganisationInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setFullname( qry.record().value( tr( "fullname" ) ).toString() );
    info->setHumanIdentifier( qry.record().value( tr( "humanIdentifier" ) ) );
    info->setAddress( qry.record().value( tr( "address" ) ).toString() );
    info->setPhone( qry.record().value( tr( "phone" ) ).toString() );
    info->setEmail( qry.record().value( tr( "email" ) ).toString() );
    emit sendInfo( info );
  }
}

OrganisationLoader_P::OrganisationLoader_P( OrganisationLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

OrganisationLoader_P::~OrganisationLoader_P()
{
}

OrganisationLoader * OrganisationLoader_P::p_dptr() const
{
  return qobject_cast<OrganisationLoader *>( parent() );
}
