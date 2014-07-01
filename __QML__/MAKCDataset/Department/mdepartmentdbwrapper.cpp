#include "mdepartmentdbwrapper.h"

#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MDepartment ]*
*/
MDepartment::MDepartment( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{}

MDepartment::~MDepartment() {}

QVariant MDepartment::identifier() const
{
  return m__Identifier;
}

void MDepartment::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MDepartment::name() const
{
  return m__Name;
}

void MDepartment::setName( const QString & name )
{
  m__Name = name;

  emit nameChanged();
}

int MDepartment::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MDepartment::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MDepartment::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MDepartment ]*
*/


/*
 * Begin C++ class definition: *[ MDepartmentDBWrapper ]*
*/
MDepartmentDBWrapper::MDepartmentDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MDepartmentDBWrapper::~MDepartmentDBWrapper()
{
  m__ExistDepartments.clear();
}

MDepartment * MDepartmentDBWrapper::department( QVariant identifier )
{
  MDepartment *result = NULL;

  locker()->lockForRead();
  result = m__ExistDepartments.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM departments WHERE id=%1" ).arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() || !qry->next() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "id" ).toInt();
    locker()->lockForWrite();
    result = new MDepartment;
    result->moveToThread( parent()->thread() );
    m__ExistDepartments[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry->record().value( "aname" ).toString() );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MDepartment *> MDepartmentDBWrapper::departments( QVariantList identifiers )
{
  QList<MDepartment *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MDepartment *department = m__ExistDepartments.value( identifier.toInt(), NULL );

    if ( department == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << department;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM departments WHERE id in (%1)" ).arg( ids );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MDepartment *department = new MDepartment;
      department->moveToThread( parent()->thread() );
      m__ExistDepartments[identifier] = department;
      department->setIdentifier( identifier );
      department->setName( qry->record().value( "aname" ).toString() );
      result << department;
    }
    qry->clear();
    delete qry;
    qry = NULL;
  }
  locker()->unlock();

  return result;
}

bool MDepartmentDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM departments ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM departments WHERE %1 ORDER BY id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(id) FROM departments" );
  else maxIdQuery = tr( "SELECT max(id) FROM departments WHERE %1" ).arg( maxIdQuery );

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
      MDepartment *oldDepartment = qobject_cast<MDepartment *>( pTake( (int)Founded, 0 ) );

      if ( oldDepartment->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDepartment ) == -1 )
      {
        m__ExistDepartments.remove( oldDepartment->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldDepartment, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MDepartment *department = m__ExistDepartments.value( identifier, NULL );

      int departmentsCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < departmentsCount; index++ )
      {
        MDepartment *oldDepartment = qobject_cast<MDepartment *>( pObject( (int)Founded, index ) );

        if ( identifier > oldDepartment->identifier().toInt() || maxId < oldDepartment->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          departmentsCount--;

          if ( oldDepartment->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDepartment ) == -1 )
          {
            m__ExistDepartments.remove( oldDepartment->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldDepartment, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldDepartment->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( department == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        department = new MDepartment;
        department->moveToThread( parent()->thread() );
        m__ExistDepartments[identifier] = department;
        department->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, department, lastFounded );
      }
      department->setName( qry->record().value( "aname" ).toString() );
    }
    //  LogDebug() << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;

  return true;
}

bool MDepartmentDBWrapper::initiating()
{
  return true;
}

bool MDepartmentDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MDepartmentDBWrapper ]*
*/
