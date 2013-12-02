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
  if ( !qry.exec( tr( "SELECT id AS identifier, declar_id AS declarIdentifier,"
                      " trustee_id AS trusteeClientIdentifier,"
                      " client_id AS clientIdentifier"
                      " FROM declar_trustees%1 ORDER BY id" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    TrusteeInfo info;
    info.setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info.setDeclarIdentifier( qry.record().value( tr( "declarIdentifier" ) ) );
    info.setTrusteeClientIdentifier( qry.record().value( tr( "trusteeClientIdentifier" ) ) );
    info.setClientIdentifier( qry.record().value( tr( "clientIdentifier" ) ) );
    emit sendTrusteeInfo( info );
  }
}

TrusteeLoader_P::TrusteeLoader_P( TrusteeLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__ErrorLastId(-1),
  m__Errors(QHash<int, QString>()),
  m__ConnectionName(QString()),
  m__Source(NULL)
{
  connect( this, SIGNAL(sendError(QString)), parent, SLOT(receivedError(QString)) );
  qRegisterMetaType<TrusteeInfo>("TrusteeInfo");
}

TrusteeLoader_P::~TrusteeLoader_P()
{
  delete m__Source;
  m__Source = NULL;
}

TrusteeLoader * TrusteeLoader_P::p_dptr() const
{
  return qobject_cast<TrusteeLoader *>( parent() );
}
