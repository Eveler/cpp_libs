#include "userloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void UserLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, surname, aname AS firstname,"
                      " lastname, post, department, isactive, dismissed,"
                      " dblogin, direction_id AS direction"
                      " FROM users%1 ORDER BY surname, aname, lastname" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    UserInfo *info = new UserInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setSurname( qry.record().value( tr( "surname" ) ).toString() );
    info->setFirstname( qry.record().value( tr( "firstname" ) ).toString() );
    info->setLastname( qry.record().value( tr( "lastname" ) ).toString() );
    info->setPostIdentifier( qry.record().value( tr( "post" ) ) );
    info->setDepartmentIdentifier( qry.record().value( tr( "department" ) ) );
    info->setIsactive( qry.record().value( tr( "isactive" ) ).toBool() );
    info->setDismissed( qry.record().value( tr( "dismissed" ) ).toBool() );
    info->setDblogin( qry.record().value( tr( "dblogin" ) ).toString() );
    info->setDirectionIdentifier( qry.record().value( tr( "direction" ) ) );
    emit sendInfo( info );
  }
}

UserLoader_P::UserLoader_P( UserLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

UserLoader_P::~UserLoader_P()
{
}

UserLoader * UserLoader_P::p_dptr() const
{
  return qobject_cast<UserLoader *>( parent() );
}
