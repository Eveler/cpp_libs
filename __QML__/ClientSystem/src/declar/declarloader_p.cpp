#include "declarloader_p.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>


void DeclarLoader_P::run()
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
  if ( !qry.exec( tr( "SELECT id AS identifier, srvid AS serviceIdentifier,"
                      " declarnum AS number, datein AS createDate, ctrldate AS controlDate,"
                      " respite_date AS respiteDate, enddate AS closeDate,"
                      " addr AS firstLandmark, addr1 AS lastLandmark,"
                      " upravlenieid AS directionIdentifier, responsible AS responsibleIdentifier,"
                      " decowner AS ownerIdentifier, isnew, deleted, resultsid AS resultIdentifier,"
                      " assessment_type_id AS assessmentTypeIdentifier, assessment_id AS assessmentIdentifier,"
                      " result_ways_id AS resultWayIdentifier"
                      " FROM declars%1 ORDER BY declarnum" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( qry.lastError().text() ) );
    return;
  }
  while ( qry.next() )
  {
    DeclarInfo *info = new DeclarInfo();
    info->setIdentifier( qry.record().value( tr( "identifier" ) ) );
    info->setServiceIdentifier( qry.record().value( tr( "serviceIdentifier" ) ) );
    info->setNumber( qry.record().value( tr( "number" ) ).toInt() );
    info->setCreateDate( qry.record().value( tr( "createDate" ) ).toDateTime() );
    info->setControlDate( qry.record().value( tr( "controlDate" ) ).toDateTime() );
    info->setRespiteDate( qry.record().value( tr( "respiteDate" ) ).toDateTime() );
    info->setCloseDate( qry.record().value( tr( "closeDate" ) ).toDateTime() );
    info->setFirstLandmark( qry.record().value( tr( "firstLandmark" ) ).toString() );
    info->setLastLandmark( qry.record().value( tr( "lastLandmark" ) ).toString() );
    info->setDirectionIdentifier( qry.record().value( tr( "directionIdentifier" ) ) );
    info->setResponsibleIdentifier( qry.record().value( tr( "responsibleIdentifier" ) ) );
    info->setOwnerIdentifier( qry.record().value( tr( "ownerIdentifier" ) ) );
    info->setIsnew( qry.record().value( tr( "isnew" ) ).toBool() );
    info->setDeleted( qry.record().value( tr( "deleted" ) ).toBool() );
    info->setResultIdentifier( qry.record().value( tr( "resultIdentifier" ) ) );
    info->setAssessmentTypeIdentifier( qry.record().value( tr( "assessmentTypeIdentifier" ) ) );
    info->setAssessmentIdentifier( qry.record().value( tr( "assessmentIdentifier" ) ) );
    info->setResultWayIdentifier( qry.record().value( tr( "resultWayIdentifier" ) ) );
    emit sendInfo( info );
  }
}

DeclarLoader_P::DeclarLoader_P( DeclarLoader *parent ) :
  QThread(parent),
  m__Successfully(true),
  m__LastError(QString()),
  m__ConnectionName(QString())
{
}

DeclarLoader_P::~DeclarLoader_P()
{
}

DeclarLoader * DeclarLoader_P::p_dptr() const
{
  return qobject_cast<DeclarLoader *>( parent() );
}
