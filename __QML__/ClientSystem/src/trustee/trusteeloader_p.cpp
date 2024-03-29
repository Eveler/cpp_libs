#include "trusteeloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>


void TrusteeLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT COUNT(*) FROM declar_trustees%1" )
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
  if ( !m__Query->exec( tr( "SELECT id AS identifier, declar_id AS declarIdentifier,"
                      " trustee_id AS trusteeClientIdentifier, client_id AS clientIdentifier"
                      " FROM declar_trustees%1 ORDER BY declar_id, trustee_id, client_id" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    return;
  }
}

TrusteeLoader_P::TrusteeLoader_P( TrusteeLoader *parent ) :
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

TrusteeLoader_P::~TrusteeLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

TrusteeLoader * TrusteeLoader_P::p_dptr() const
{
  return qobject_cast<TrusteeLoader *>( parent() );
}

TrusteeInfo * TrusteeLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    TrusteeInfo *info = new TrusteeInfo();
    info->setIdentifier( m__Query->record().value( tr( "identifier" ) ) );
    info->setDeclarIdentifier( m__Query->record().value( tr( "declarIdentifier" ) ) );
    info->setTrusteeClientIdentifier( m__Query->record().value( tr( "trusteeClientIdentifier" ) ) );
    info->setClientIdentifier( m__Query->record().value( tr( "clientIdentifier" ) ) );
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
