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
  if ( !qry.exec( tr( "SELECT COUNT (*) FROM declars%1" )
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
  if ( !m__Query->exec( tr( "SELECT id AS identifier, srvid AS serviceIdentifier,"
                            " declarnum AS number, datein AS createDate, ctrldate AS controlDate,"
                            " respite_date AS respiteDate, enddate AS closeDate,"
                            " addr AS firstLandmark, addr1 AS lastLandmark,"
                            " upravlenieid AS directionIdentifier, responsible AS responsibleIdentifier,"
                            " decowner AS ownerIdentifier, isnew, deleted, resultsid AS resultIdentifier,"
                            " assessment_type_id AS assessmentTypeIdentifier, assessment_id AS assessmentIdentifier,"
                            " result_ways_id AS resultWayIdentifier,"
                            " array_to_string(ARRAY(SELECT dc.id FROM declar_clients dc WHERE d.id=dc.declar_id), ';') AS declarClientIdentifiers,"
                            " array_to_string(ARRAY(SELECT dt.id FROM declar_trustees dt WHERE d.id=dt.declar_id), ';') AS declarTrusteeIdentifiers"
                            " FROM declars d%1 ORDER BY declarnum" )
                  .arg( ( !m__Filter.isEmpty() ? " WHERE "+m__Filter : "" ) ) ) )
  {
    m__Successfully = false;
    emit sendError( tr( "Query error:\n%1" ).arg( m__Query->lastError().text() ) );
    return;
  }
}

DeclarLoader_P::DeclarLoader_P( DeclarLoader *parent ) :
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

DeclarLoader_P::~DeclarLoader_P()
{
  if ( m__Query != NULL )
  {
    delete m__Query;
    m__Query = NULL;
  }
}

DeclarLoader * DeclarLoader_P::p_dptr() const
{
  return qobject_cast<DeclarLoader *>( parent() );
}

DeclarInfo * DeclarLoader_P::newInfo()
{
  if ( m__Query != NULL && m__Query->next() )
  {
    DeclarInfo *info = new DeclarInfo();
    info->setIdentifier( m__Query->record().value( tr( "identifier" ) ) );
    info->setServiceIdentifier( m__Query->record().value( tr( "serviceIdentifier" ) ) );
    info->setNumber( m__Query->record().value( tr( "number" ) ).toInt() );
    info->setCreateDate( m__Query->record().value( tr( "createDate" ) ).toDateTime() );
    info->setControlDate( m__Query->record().value( tr( "controlDate" ) ).toDateTime() );
    info->setRespiteDate( m__Query->record().value( tr( "respiteDate" ) ).toDateTime() );
    info->setCloseDate( m__Query->record().value( tr( "closeDate" ) ).toDateTime() );
    info->setFirstLandmark( m__Query->record().value( tr( "firstLandmark" ) ).toString() );
    info->setLastLandmark( m__Query->record().value( tr( "lastLandmark" ) ).toString() );
    info->setDirectionIdentifier( m__Query->record().value( tr( "directionIdentifier" ) ) );
    info->setResponsibleIdentifier( m__Query->record().value( tr( "responsibleIdentifier" ) ) );
    info->setOwnerIdentifier( m__Query->record().value( tr( "ownerIdentifier" ) ) );
    info->setIsnew( m__Query->record().value( tr( "isnew" ) ).toBool() );
    info->setDeleted( m__Query->record().value( tr( "deleted" ) ).toBool() );
    info->setResultIdentifier( m__Query->record().value( tr( "resultIdentifier" ) ) );
    info->setAssessmentTypeIdentifier( m__Query->record().value( tr( "assessmentTypeIdentifier" ) ) );
    info->setAssessmentIdentifier( m__Query->record().value( tr( "assessmentIdentifier" ) ) );
    info->setResultWayIdentifier( m__Query->record().value( tr( "resultWayIdentifier" ) ) );
    QList<QVariant> identifiers;
    foreach ( QString identifier, m__Query->record().value( tr( "declarClientIdentifiers" ) ).toString().split( ";" ) )
      identifiers << identifier.toInt();
    info->setDeclarClientIdentifiers( identifiers );
    identifiers.clear();
    foreach ( QString identifier, m__Query->record().value( tr( "declarTrusteeIdentifiers" ) ).toString().split( ";" ) )
      identifiers << identifier.toInt();
    info->setDeclarTrusteeIdentifiers( identifiers );
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
