#include "mservicedbwrapper.h"

#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


/*
 * Begin C++ - QML class definition: *[ MService ]*
*/
MService::MService( QQuickItem *parent ) :
  QQuickItem(parent),
  m__Subservices(new MDataSourceModel( this )),
  m__ExternalLinksCount(0)
{}

MService::~MService() {}

QVariant MService::identifier() const
{
  return m__Identifier;
}

void MService::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MService::index() const
{
  return m__Index;
}

void MService::setIndex( const QString &index )
{
  m__Index = index;

  emit indexChanged();
}

const QString & MService::name() const
{
  return m__Name;
}

void MService::setName( const QString &name )
{
  m__Name = name;

  emit nameChanged();
}

int MService::deadline() const
{
  return m__Deadline;
}

void MService::setDeadline( int deadline )
{
  m__Deadline = deadline;

  emit deadlineChanged();
}

bool MService::workdays() const
{
  return m__Workdays;
}

void MService::setWorkdays( bool workdays )
{
  m__Workdays = workdays;

  emit workdaysChanged();
}

bool MService::isactive() const
{
  return m__Isactive;
}

void MService::setIsactive( bool isactive )
{
  m__Isactive = isactive;

  emit isactiveChanged();
}

MDataSourceModel * MService::subservices() const
{
  return m__Subservices;
}

int MService::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MService::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MService::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MService ]*
*/


/*
 * Begin C++ class definition: *[ MServiceDBWrapper ]*
*/
MServiceDBWrapper::MServiceDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MServiceDBWrapper::~MServiceDBWrapper()
{
  m__ExistServices.clear();
}

MService * MServiceDBWrapper::service( QVariant identifier )
{
  MService *result = NULL;

  locker()->lockForRead();
  result = m__ExistServices.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT srvs.*, srvn.srvname FROM ctrldatesrvs srvs, service_names srvn WHERE srvs.srv_name_id=srvn.id AND srvs.id=%1" )
                           .arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() || !qry->next() )
    {
      qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "id" ).toInt();
    locker()->lockForWrite();
    result = new MService;
    result->moveToThread( parent()->thread() );
    m__ExistServices[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry->record().value( "srvname" ).toString() );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MService *> MServiceDBWrapper::services( QVariantList identifiers )
{
  QList<MService *> result;

  locker()->lockForWrite();
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MService *service = m__ExistServices.value( identifier.toInt(), NULL );

    if ( service != NULL ) result << service;
  }
  locker()->unlock();

  return result;
}

void MServiceDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
  MAbstractDBWrapper::job( objectiveType, objectiveValue );
}

bool MServiceDBWrapper::searching( const QString &queryText )
{
  Q_UNUSED(queryText)

  return true;
}

bool MServiceDBWrapper::searching( MService *parentService )
{
  QString currentQuery;
  if ( parentService == NULL )
    currentQuery = tr( "SELECT srvs.*, srvn.srvname FROM ctrldatesrvs srvs, service_names srvn"
                       " WHERE srvs.srv_name_id=srvn.id AND srvs.root=%1 ORDER BY srvs.id" ).arg( parentService->identifier().toString() );
  else
    currentQuery = tr( "SELECT srvs.*, srvn.srvname FROM ctrldatesrvs srvs, service_names srvn"
                       " WHERE srvs.srv_name_id=srvn.id AND (srvs.root IS NULL OR srvs.root=0 OR srvs.id=srvs.root) ORDER BY srvs.id" );
  QString maxIdQuery;
  if ( parentService == NULL )
    maxIdQuery = tr( "SELECT max(srvs.id) FROM ctrldatesrvs srvs, service_names srvn WHERE srvs.srv_name_id=srvn.id"
                     " AND srvs.root=%1" ).arg( parentService->identifier().toString() );
  else
    maxIdQuery = tr( "SELECT max(srvs.id) FROM ctrldatesrvs srvs, service_names srvn WHERE srvs.srv_name_id=srvn.id"
                     " AND (srvs.root IS NULL OR srvs.root=0 OR srvs.id=srvs.root)" );

  QSqlQuery *qry = MDatabase::instance()->getQuery( maxIdQuery, connectionName() );
  if ( qry->lastError().isValid() || !qry->next() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }
  int maxId = qry->record().value( 0 ).toInt();
  qry->clear();
  delete qry;
  qry = NULL;

  qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }

  locker()->lockForWrite();

  if ( maxId == 0 )
  {
    if ( parentService == NULL )
      while ( pCount( (int)Founded ) > 0 )
      {
        MService *oldService = qobject_cast<MService *>( pTake( (int)Founded, 0 ) );

        if ( oldService->externalLinksCount() == 0 && pIndex( (int)Initiated, oldService ) == -1 )
        {
          m__ExistServices.remove( oldService->identifier().toInt() );
          connect( this, SIGNAL(aboutToReleaseOldResources()), oldService, SLOT(deleteLater()) );
        }
      }
    else
      while ( pCount( parentService->subservices() ) )
      {
        MService *oldService = qobject_cast<MService *>( pTake( parentService->subservices(), 0 ) );

        if ( oldService->externalLinksCount() == 0 && pIndex( (int)Initiated, oldService ) == -1 )
        {
          m__ExistServices.remove( oldService->identifier().toInt() );
          connect( this, SIGNAL(aboutToReleaseOldResources()), oldService, SLOT(deleteLater()) );
        }
      }
  }
  else
  {
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MService *service = m__ExistServices.value( identifier, NULL );

      int servicesCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < servicesCount; index++ )
      {
        MService *oldService = qobject_cast<MService *>( pObject( (int)Founded, index ) );

        if ( identifier > oldService->identifier().toInt() || maxId < oldService->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          servicesCount--;

          if ( oldService->externalLinksCount() == 0 && pIndex( (int)Initiated, oldService ) == -1 )
          {
            m__ExistServices.remove( oldService->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldService, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldService->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( service == NULL )
      {
        //      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
        service = new MService;
        service->moveToThread( parent()->thread() );
        m__ExistServices[identifier] = service;
        service->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, service, lastFounded );
      }
      service->setName( qry->record().value( "aname" ).toString() );
    }
    //  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;
}

bool MServiceDBWrapper::initiating()
{
  return true;
}

bool MServiceDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MServiceDBWrapper ]*
*/
