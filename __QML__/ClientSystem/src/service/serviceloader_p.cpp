#include "serviceloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>


void ServiceLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT COUNT(*) FROM"
                      "  (SELECT s.id AS identifier, s.root, s.\"sIdx\" AS sidx,"
                      "     sn.srvname AS name, s.deadline, s.workdays, s.isactive"
                      "    FROM ctrldatesrvs s, service_names sn"
                      "    WHERE s.srv_name_id=sn.id) q_1%1" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE ("+m__Filter+")" : "" ) ) ) )
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
  if ( !m__Query->exec( tr( "SELECT q_1.* FROM"
                      "  (SELECT s.id AS identifier, s.root, s.\"sIdx\" AS sidx,"
                      "     sn.srvname AS name, s.deadline, s.workdays, s.isactive"
                      "    FROM ctrldatesrvs s, service_names sn"
                      "    WHERE s.srv_name_id=sn.id"
                      "    ORDER BY \"sIdxFloat\") q_1%1" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE ("+m__Filter+")" : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    return;
  }
}

ServiceLoader_P::ServiceLoader_P( ServiceLoader *parent ) :
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

ServiceLoader_P::~ServiceLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

ServiceLoader * ServiceLoader_P::p_dptr() const
{
  return qobject_cast<ServiceLoader *>( parent() );
}

ServiceInfo * ServiceLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    ServiceInfo *info = new ServiceInfo();
    info->setIdentifier( m__Query->record().value( tr( "identifier" ) ) );
    info->setRoot( m__Query->record().value( tr( "root" ) ) );
    info->setSidx( m__Query->record().value( tr( "sidx" ) ).toString() );
    info->setName( m__Query->record().value( tr( "name" ) ).toString() );
    info->setDeadline( m__Query->record().value( tr( "deadline" ) ).toInt() );
    info->setWorkdays( m__Query->record().value( tr( "workdays" ) ).toBool() );
    info->setIsactive( m__Query->record().value( tr( "isactive" ) ).toBool() );
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
