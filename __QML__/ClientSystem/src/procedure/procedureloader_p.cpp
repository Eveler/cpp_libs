#include "procedureloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void ProcedureLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT proc_id AS identifier, proc_name AS name"
                      " FROM proc_tbl%1 ORDER BY proc_name" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    ProcedureInfo *info = new ProcedureInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setName( qry.record().value( tr( "name" ) ).toString() );
    emit sendInfo( info );
  }
}

ProcedureLoader_P::ProcedureLoader_P( ProcedureLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

ProcedureLoader_P::~ProcedureLoader_P()
{
}

ProcedureLoader * ProcedureLoader_P::p_dptr() const
{
  return qobject_cast<ProcedureLoader *>( parent() );
}
