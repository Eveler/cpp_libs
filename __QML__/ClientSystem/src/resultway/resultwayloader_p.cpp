#include "resultwayloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
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
  if ( !qry.exec( tr( "SELECT COUNT(*) FROM result_ways%1" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  qry.next();
  m__AvailableCount = qry.record().value( 0 ).toInt();
  m__ReceivedCount = 0;
  emit availableCountChanged();
  qry.clear();
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
  if ( m__AvailableCount == 0 ) return;
  m__Query = new QSqlQuery( db );
  if ( !m__Query->exec( tr( "SELECT id AS identifier, result_way_name AS name"
                      " FROM result_ways%1 ORDER BY result_way_name" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    return;
  }
}

ResultwayLoader_P::ResultwayLoader_P( ResultwayLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__Started(false),
  m__LastError(QString()),
  m__ConnectionName(QString()),
  m__Filter(QString()),
  m__Query(NULL),
  m__AvailableCount(0),
  m__ReceivedCount(0)
{
}

ResultwayLoader_P::~ResultwayLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

ResultwayLoader * ResultwayLoader_P::p_dptr() const
{
  return qobject_cast<ResultwayLoader *>( parent() );
}

ResultwayInfo * ResultwayLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    ResultwayInfo *info = new ResultwayInfo();
    info->setIdentifier( m__Query->record().value( tr( "identifier" ) ) );
    info->setName( m__Query->record().value( tr( "name" ) ).toString() );
    m__ReceivedCount++;
    if ( m__ReceivedCount == m__AvailableCount )
    {
      delete m__Query;
      m__Query = NULL;
    }
    return info;
  }
  return NULL;
}
