#include "clientloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
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
  if ( !qry.exec( tr( "SELECT COUNT(*) FROM clientlist%1" )
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
  if ( !m__Query->exec( tr( "SELECT id AS identifier, clid, isorg"
                      " FROM clientlist%1 ORDER BY clname" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    delete m__Query;
    m__Query = NULL;
    return;
  }
}

ClientLoader_P::ClientLoader_P( ClientLoader *parent ) :
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

ClientLoader_P::~ClientLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

ClientLoader * ClientLoader_P::p_dptr() const
{
  return qobject_cast<ClientLoader *>( parent() );
}

ClientInfo * ClientLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    ClientInfo *info = new ClientInfo();
    info->setIdentifier( m__Query->record().value( tr( "identifier" ) ) );
    if ( m__Query->record().value( tr( "isorg" ) ).toInt() == 1 )
    {
      info->setOrganisationIdentifier( m__Query->record().value( tr( "clid" ) ).toString() );
      info->setHumanIdentifier( QVariant() );
    }
    else
    {
      info->setOrganisationIdentifier( QVariant() );
      info->setHumanIdentifier( m__Query->record().value( tr( "clid" ) ).toString() );
    }
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
