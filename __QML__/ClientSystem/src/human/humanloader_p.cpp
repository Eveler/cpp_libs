#include "humanloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void HumanLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, surname, firstname, lastname,"
                      " addr AS address, phone, \"e-mail\" AS email"
                      " FROM humans%1 ORDER BY surname, firstname, lastname" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    HumanInfo *info = new HumanInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setSurname( qry.record().value( tr( "surname" ) ).toString() );
    info->setFirstname( qry.record().value( tr( "firstname" ) ).toString() );
    info->setLastname( qry.record().value( tr( "lastname" ) ).toString() );
    info->setAddress( qry.record().value( tr( "address" ) ).toString() );
    info->setPhone( qry.record().value( tr( "phone" ) ).toString() );
    info->setEmail( qry.record().value( tr( "email" ) ).toString() );
    emit sendInfo( info );
  }
}

HumanLoader_P::HumanLoader_P( HumanLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

HumanLoader_P::~HumanLoader_P()
{
}

HumanLoader * HumanLoader_P::p_dptr() const
{
  return qobject_cast<HumanLoader *>( parent() );
}
