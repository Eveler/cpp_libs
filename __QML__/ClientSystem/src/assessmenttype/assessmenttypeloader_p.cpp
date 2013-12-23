#include "assessmenttypeloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void AssessmenttypeLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT COUNT(*) FROM assessment_types%1" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  qry.next();
  m__Count = qry.record().value( 0 ).toInt();
  emit countChanged();
  qry.clear();
  if ( !qry.exec( tr( "SELECT id AS identifier, ass_type AS name"
                      " FROM assessment_types%1 ORDER BY ass_type" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    AssessmenttypeInfo *info = new AssessmenttypeInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setName( qry.record().value( tr( "name" ) ).toString() );
    emit sendInfo( info );
  }
  qry.clear();
  db.close();
}

AssessmenttypeLoader_P::AssessmenttypeLoader_P( AssessmenttypeLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__Started(false),
  m__LastError(QString()),
  m__ConnectionName(QString()),
  m__Filter(QString()),
  m__Count(0)
{
}

AssessmenttypeLoader_P::~AssessmenttypeLoader_P()
{
}

AssessmenttypeLoader * AssessmenttypeLoader_P::p_dptr() const
{
  return qobject_cast<AssessmenttypeLoader *>( parent() );
}
