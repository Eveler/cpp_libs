#include "trusteeloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
  if ( !qry.exec( tr( "SELECT trustee_id AS identifier, declar_id AS declarIdentifier,"
                      " client_id AS clientIdentifier"
                      " FROM declar_trustees%1 ORDER BY declar_id, trustee_id, client_id" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  TrusteeInfo *info = NULL;
  while ( qry.next() )
  {
    QVariant identifier = qry.record().value( tr( "identifier" ) );
    QVariant declarIdentifier = qry.record().value( tr( "declarIdentifier" ) );
    QVariant clientIdentifier = qry.record().value( tr( "clientIdentifier" ) );
    if ( info != NULL )
    {
      if ( info->identifier() == identifier )
        info->addClientIdentifier( clientIdentifier );
      else
      {
        emit sendInfo( info );
        info = NULL;
      }
    }

    if ( info == NULL )
    {
      info = new TrusteeInfo();
      info->setIdentifier( identifier );
      info->setDeclarIdentifier( declarIdentifier );
      info->addClientIdentifier( clientIdentifier );
    }
  }
  if ( info != NULL )
  {
    emit sendInfo( info );
    info = NULL;
  }
}

TrusteeLoader_P::TrusteeLoader_P( TrusteeLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

TrusteeLoader_P::~TrusteeLoader_P()
{
}

TrusteeLoader * TrusteeLoader_P::p_dptr() const
{
  return qobject_cast<TrusteeLoader *>( parent() );
}
