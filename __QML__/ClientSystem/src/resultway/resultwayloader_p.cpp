#include "resultwayloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void ResultwayLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, result_way_name AS name"
                      " FROM result_ways%1 ORDER BY result_way_name" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    ResultwayInfo *info = new ResultwayInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setName( qry.record().value( tr( "name" ) ).toString() );
    emit sendInfo( info );
  }
}

ResultwayLoader_P::ResultwayLoader_P( ResultwayLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

ResultwayLoader_P::~ResultwayLoader_P()
{
}

ResultwayLoader * ResultwayLoader_P::p_dptr() const
{
  return qobject_cast<ResultwayLoader *>( parent() );
}
