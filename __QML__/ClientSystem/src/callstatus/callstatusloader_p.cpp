#include "callstatusloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>


void CallstatusLoader_P::run()
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
  QString query;
  if ( m__LoadIdentifier.isValid() )
  {
    if ( !qry.exec( tr ( "SELECT COUNT(*) FROM call_statuses"
                         " WHERE id=%1" ).arg( m__LoadIdentifier.toInt() ) ) )
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

    query = tr( "SELECT id AS identifier, status AS name"
                " FROM call_statuses"
                " WHERE id=%1 ORDER BY status" ).arg( m__LoadIdentifier.toInt() );
    m__LoadIdentifier.clear();
  }
  else
  {
    if ( !qry.exec( "SELECT COUNT(*) FROM call_statuses" ) )
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

    query = tr( "SELECT id AS identifier, status AS name"
                   " FROM call_statuses ORDER BY status" );
  }
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
  if ( m__AvailableCount == 0 ) return;
  m__Query = new QSqlQuery( db );
  if ( !m__Query->exec( query ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    return;
  }
}

CallstatusLoader_P::CallstatusLoader_P( CallstatusLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__Started(false),
  m__LastError(QString()),
  m__ConnectionName(QString()),
  m__LoadIdentifier(QVariant()),
  m__Query(NULL),
  m__AvailableCount(0),
  m__ReceivedCount(0)
{
}

CallstatusLoader_P::~CallstatusLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

CallstatusLoader * CallstatusLoader_P::p_dptr() const
{
  return qobject_cast<CallstatusLoader *>( parent() );
}

CallstatusInfo * CallstatusLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    CallstatusInfo *info = new CallstatusInfo();
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
