#include "mdirectiondbwrapper.h"

#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MDirection ]*
*/
MDirection::MDirection( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{}

MDirection::~MDirection() {}

QVariant MDirection::identifier() const
{
  return m__Identifier;
}

void MDirection::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MDirection::name() const
{
  return m__Name;
}

void MDirection::setName( const QString & name )
{
  m__Name = name;

  emit nameChanged();
}

int MDirection::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MDirection::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MDirection::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MDirection ]*
*/


/*
 * Begin C++ class definition: *[ MDirectionDBWrapper ]*
*/
MDirectionDBWrapper::MDirectionDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MDirectionDBWrapper::~MDirectionDBWrapper()
{
  m__ExistDirections.clear();
}

MDirection * MDirectionDBWrapper::direction( QVariant identifier )
{
  MDirection *result = NULL;

  locker()->lockForRead();
  result = m__ExistDirections.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM directions WHERE \"directionID\"=%1" ).arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() || !qry->next() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "directionID" ).toInt();
    locker()->lockForWrite();
    result = new MDirection;
    result->moveToThread( parent()->thread() );
    m__ExistDirections[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry->record().value( "aname" ).toString() );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MDirection *> MDirectionDBWrapper::directions( QVariantList identifiers )
{
  QList<MDirection *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MDirection *direction = m__ExistDirections.value( identifier.toInt(), NULL );

    if ( direction == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << direction;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM directions WHERE \"directionID\" in (%1)" ).arg( ids );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry->next() )
    {
      int identifier = qry->record().value( "directionID" ).toInt();
      MDirection *direction = new MDirection;
      direction->moveToThread( parent()->thread() );
      m__ExistDirections[identifier] = direction;
      direction->setIdentifier( identifier );
      direction->setName( qry->record().value( "aname" ).toString() );
      result << direction;
    }
    qry->clear();
    delete qry;
    qry = NULL;
  }
  locker()->unlock();

  return result;
}

bool MDirectionDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM directions ORDER BY \"directionID\"" );
  else currentQuery = tr( "SELECT * FROM directions WHERE %1 ORDER BY \"directionID\"" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(\"directionID\") FROM directions" );
  else maxIdQuery = tr( "SELECT max(\"directionID\") FROM directions WHERE %1" ).arg( maxIdQuery );

  QSqlQuery *qry = MDatabase::instance()->getQuery( maxIdQuery, connectionName() );
  if ( qry->lastError().isValid() || !qry->next() )
  {
    LogDebug() << qry->lastError().text();
    return false;
  }
  int maxId = qry->record().value( 0 ).toInt();
  qry->clear();
  delete qry;
  qry = NULL;

  qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    LogDebug() << qry->lastError().text();
    return false;
  }

  locker()->lockForWrite();

  if ( maxId == 0 )
  {
    while ( pCount( (int)Founded ) > 0 )
    {
      MDirection *oldDirection = qobject_cast<MDirection *>( pTake( (int)Founded, 0 ) );

      if ( oldDirection->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDirection ) == -1 )
      {
        m__ExistDirections.remove( oldDirection->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldDirection, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "directionID" ).toInt();
      MDirection *direction = m__ExistDirections.value( identifier, NULL );

      int directionsCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < directionsCount; index++ )
      {
        MDirection *oldDirection = qobject_cast<MDirection *>( pObject( (int)Founded, index ) );

        if ( identifier > oldDirection->identifier().toInt() || maxId < oldDirection->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          directionsCount--;

          if ( oldDirection->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDirection ) == -1 )
          {
            m__ExistDirections.remove( oldDirection->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldDirection, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldDirection->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( direction == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        direction = new MDirection;
        direction->moveToThread( parent()->thread() );
        m__ExistDirections[identifier] = direction;
        direction->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, direction, lastFounded );
      }
      direction->setName( qry->record().value( "aname" ).toString() );
    }
    //  LogDebug() << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;

  return true;
}

bool MDirectionDBWrapper::initiating()
{
  return true;
}

bool MDirectionDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MDirectionDBWrapper ]*
*/
