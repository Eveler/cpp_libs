#include "mproceduredbwrapper.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


/*
 * Begin C++ - QML class definition: *[ MProcedure ]*
*/
MProcedure::MProcedure( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{}

MProcedure::~MProcedure() {}

QVariant MProcedure::identifier() const
{
  return m__Identifier;
}

void MProcedure::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MProcedure::name() const
{
  return m__Name;
}

void MProcedure::setName( const QString & name )
{
  m__Name = name;

  emit nameChanged();
}

int MProcedure::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MProcedure::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MProcedure::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MProcedure ]*
*/

MProcedureDBWrapper::MProcedureDBWrapper(MAbstractDataSource *parent) :
  MAbstractDBWrapper(parent)
{
}

MProcedureDBWrapper::~MProcedureDBWrapper()
{
  m__ExistProcedures.clear();
}

MProcedure * MProcedureDBWrapper::procedure( QVariant identifier )
{
  MProcedure *result = NULL;

  locker()->lockForRead();
  result = m__ExistProcedures.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM proc_tbl WHERE proc_id=%1" ).arg( identifier.toInt() );

    QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
    if ( !database.open() )
    {
      qDebug() << metaObject()->className() << __func__ << __LINE__ << database.lastError().text();
      return result;
    }

    QSqlQuery qry( currentQuery, database );
    if ( qry.lastError().isValid() || !qry.next() )
    {
      qDebug() << metaObject()->className() << __func__ << __LINE__ << qry.lastError().text();
      return result;
    }
    int identifier = qry.record().value( "proc_id" ).toInt();
    result = new MProcedure;
    result->moveToThread( parent()->thread() );
    m__ExistProcedures[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry.record().value( "aname" ).toString() );
    locker()->unlock();
    qry.clear();
  }

  return result;
}

QList<MProcedure *> MProcedureDBWrapper::procedures( QVariantList identifiers )
{
  QList<MProcedure *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MProcedure *procedure = m__ExistProcedures.value( identifier.toInt(), NULL );

    if ( procedure == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << procedure;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM proc_tbl WHERE proc_id in (%1)" ).arg( ids );
    QSqlDatabase database = QSqlDatabase::database( pConnectionName(), false );
    if ( !database.open() )
    {
      qDebug() << metaObject()->className() << __func__ << __LINE__ << database.lastError().text();
      locker()->unlock();
      return result;
    }

    QSqlQuery qry( currentQuery, database );
    if ( qry.lastError().isValid() )
    {
      qDebug() << metaObject()->className() << __func__ << __LINE__ << qry.lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry.next() )
    {
      int identifier = qry.record().value( "proc_id" ).toInt();
      MProcedure *procedure = new MProcedure;
      procedure->moveToThread( parent()->thread() );
      m__ExistProcedures[identifier] = procedure;
      procedure->setIdentifier( identifier );
      procedure->setName( qry.record().value( "aname" ).toString() );
      result << procedure;
    }
    qry.clear();
  }
  locker()->unlock();

  return result;
}

bool MProcedureDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM proc_tbl ORDER BY proc_id" );
  else currentQuery = tr( "SELECT * FROM proc_tbl WHERE %1 ORDER BY proc_id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(proc_id) FROM proc_tbl" );
  else maxIdQuery = tr( "SELECT max(proc_id) FROM proc_tbl WHERE %1" ).arg( maxIdQuery );

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QSqlQuery qry( maxIdQuery, database );
  if ( qry.lastError().isValid() || !qry.next() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }
  int maxId = qry.record().value( 0 ).toInt();
  qry.clear();

  if ( !qry.exec( currentQuery ) || qry.lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }

  locker()->lockForWrite();

  if ( maxId == 0 )
  {
    while ( pCount( (int)Founded ) > 0 )
    {
      MProcedure *oldProcedure = qobject_cast<MProcedure *>( pTake( (int)Founded, 0 ) );

      if ( oldProcedure->externalLinksCount() == 0 && pIndex( (int)Initiated, oldProcedure ) == -1 )
      {
        m__ExistProcedures.remove( oldProcedure->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldProcedure, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry.next() )
    {
      int identifier = qry.record().value( "proc_id" ).toInt();
      MProcedure *procedure = m__ExistProcedures.value( identifier, NULL );

      int proceduresCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < proceduresCount; index++ )
      {
        MProcedure *oldProcedure = qobject_cast<MProcedure *>( pObject( (int)Founded, index ) );

        if ( identifier > oldProcedure->identifier().toInt() || maxId < oldProcedure->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          proceduresCount--;

          if ( oldProcedure->externalLinksCount() == 0 && pIndex( (int)Initiated, oldProcedure ) == -1 )
          {
            m__ExistProcedures.remove( oldProcedure->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldProcedure, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldProcedure->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( procedure == NULL )
      {
        //      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
        procedure = new MProcedure;
        procedure->moveToThread( parent()->thread() );
        m__ExistProcedures[identifier] = procedure;
        procedure->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, procedure, lastFounded );
      }
      procedure->setName( qry.record().value( "aname" ).toString() );
    }
    //  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry.clear();

  return true;
}

bool MProcedureDBWrapper::initiating()
{
  return true;
}

bool MProcedureDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MProcedureDBWrapper ]*
*/
