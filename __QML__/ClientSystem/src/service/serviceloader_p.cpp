#include "serviceloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
  if ( !qry.exec( tr( "SELECT q_1.* FROM"
                      "  (SELECT s.id AS identifier, s.root, s.\"sIdx\" AS sidx,"
                      "     sn.srvname AS name, s.deadline, s.workdays, s.isactive"
                      "    FROM ctrldatesrvs s, service_names sn"
                      "    WHERE s.srv_name_id=sn.id"
                      "    ORDER BY \"sIdxFloat\") q_1%1" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE ("+m__Filter+")" : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    ServiceInfo *info = new ServiceInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setRoot( qry.record().value( tr( "root" ) ) );
    info->setSidx( qry.record().value( tr( "sidx" ) ).toString() );
    info->setName( qry.record().value( tr( "name" ) ).toString() );
    info->setDeadline( qry.record().value( tr( "deadline" ) ).toInt() );
    info->setWorkdays( qry.record().value( tr( "workdays" ) ).toBool() );
    info->setIsactive( qry.record().value( tr( "isactive" ) ).toBool() );
    emit sendInfo( info );
  }
}

ServiceLoader_P::ServiceLoader_P( ServiceLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

ServiceLoader_P::~ServiceLoader_P()
{
}

ServiceLoader * ServiceLoader_P::p_dptr() const
{
  return qobject_cast<ServiceLoader *>( parent() );
}
