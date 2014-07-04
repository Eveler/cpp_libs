#include "mabstractdbwrapper.h"

#include "mabstractdatasource.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QUuid>
#include <QSqlDriver>


/*
 * Begin C++ class definition: *[ MAbstractDBWrapper ]*
*/
MAbstractDBWrapper::MAbstractDBWrapper( MAbstractDataSource *parent ) :
  QThread(parent),
  ObjectListPrivate(),
  m__Locker(new QReadWriteLock),
  m__ObjectiveType(None)
{}

MAbstractDBWrapper::~MAbstractDBWrapper()
{
  if ( !m__Locker->tryLockForWrite() )
  {
    m__Locker->unlock();
    m__Locker->lockForWrite();
  }

  while ( pCount( (int)Founded ) > 0 )
  {
    QObject *object = pTake( (int)Founded, 0 );
    int index = pIndex( (int)Selected, object );
    if ( index != -1 ) pTake( (int)Selected, index );
    delete object;
//    object = NULL;
  }
  while ( pCount( (int)Initiated ) > 0 )
  {
    QObject *object = pTake( (int)Initiated, 0 );
    delete object;
    object = NULL;
  }
  while ( pCount( (int)Selected ) > 0 )
  {
    QObject *object = pTake( (int)Selected, 0 );
    delete object;
    object = NULL;
  }
  QVariantList sourceTypes = this->sourceTypes();
  foreach ( QVariant sourceType, sourceTypes )
  {
    if ( sourceType.type() == QVariant::Int )
    {
      while ( pCount( sourceType.toInt() ) > 0 )
      {
        QObject *object = pTake( sourceType.toInt(), 0 );
        delete object;
        object = NULL;
      }
    }
    else
    {
      QObject *objSource = sourceType.value<QObject *>();
      while ( pCount( objSource ) > 0 )
      {
        QObject *object = pTake( objSource, 0 );
        delete object;
        object = NULL;
      }
    }
  }
  m__Locker->unlock();
}

void MAbstractDBWrapper::setParent( MAbstractDataSource *parent )
{
  QThread::setParent( parent );
}

QString MAbstractDBWrapper::connectionName() const
{
  locker()->lockForRead();
  QString result = m__ConnectionName;
  locker()->unlock();

  return result;
}

bool MAbstractDBWrapper::setConnectionName( const QString & connectionName )
{
  if ( isRunning() ) return false;

  locker()->lockForWrite();
  m__ConnectionName = connectionName;
  locker()->unlock();

  return true;
}

QString MAbstractDBWrapper::error() const
{
  locker()->lockForRead();
  QString result = m__Error;
  locker()->unlock();

  return result;
}

bool MAbstractDBWrapper::find( const QString &filter )
{
  if ( isRunning() ) return false;

  setObjective( (int)Searching, filter );

  start();
  return true;
}

bool MAbstractDBWrapper::initiate()
{
  if ( isRunning() ) return false;

  setObjective( (int)Initiating, QVariant() );

  start();
  return true;
}

bool MAbstractDBWrapper::select( int indexInFounded )
{
  if ( isRunning() ) return false;

  locker()->lockForRead();
  QObject *object = pObject( (int)Founded, indexInFounded );
  locker()->unlock();
  if ( object == NULL ) return false;

  locker()->lockForWrite();
  pInsert( (int)Selected, object );
  locker()->unlock();

  return true;
}

bool MAbstractDBWrapper::save( QObject *object )
{
  if ( isRunning() || object == NULL ) return false;

  setObjective( (int)Saving, QVariant::fromValue( object ) );

  start();
  return true;
}

QObject * MAbstractDBWrapper::object( int sourceType, int index ) const
{
  locker()->lockForRead();
  QObject *result = pObject( sourceType, index );
  locker()->unlock();

  return result;
}

int MAbstractDBWrapper::count( int sourceType ) const
{
  locker()->lockForRead();
  int result = pCount( sourceType );
  locker()->unlock();

  return result;
}

int MAbstractDBWrapper::index( int sourceType, QObject *object ) const
{
  locker()->lockForRead();
  int result = pIndex( sourceType, object );
  locker()->unlock();

  return result;
}

QObject * MAbstractDBWrapper::object( QObject *sourceType, int index ) const
{
  locker()->lockForRead();
  QObject *result = pObject( sourceType, index );
  locker()->unlock();

  return result;
}

int MAbstractDBWrapper::count( QObject * sourceType ) const
{
  locker()->lockForRead();
  int result = pCount( sourceType );
  locker()->unlock();

  return result;
}

int MAbstractDBWrapper::index( QObject *sourceType, QObject *object ) const
{
  locker()->lockForRead();
  int result = pIndex( sourceType, object );
  locker()->unlock();

  return result;
}

void MAbstractDBWrapper::releaseOldResources()
{
  emit aboutToReleaseOldResources();
}

QReadWriteLock * MAbstractDBWrapper::locker() const
{
  return m__Locker;
}

const QString & MAbstractDBWrapper::pConnectionName() const
{
  return m__ConnectionName;
}

void MAbstractDBWrapper::setError( const QString &error )
{
  m__Error = error;
}

const QString & MAbstractDBWrapper::pError() const
{
  return m__Error;
}

void MAbstractDBWrapper::setObjective( int objectiveType, QVariant objectiveValue )
{
  locker()->lockForWrite();
  m__ObjectiveType = objectiveType;
  m__ObjectiveValue = objectiveValue;
  locker()->unlock();
}

void MAbstractDBWrapper::run()
{
  locker()->lockForWrite();
  setError( QString() );
  locker()->unlock();
  QPair<int, QVariant> objective = this->objective();
  job( objective.first, objective.second );
}

QPair<int, QVariant> MAbstractDBWrapper::objective()
{
  locker()->lockForRead();
  QPair<int, QVariant> result = qMakePair( m__ObjectiveType, m__ObjectiveValue );
  m__ObjectiveType = (int)None;
  m__ObjectiveValue.clear();
  locker()->unlock();

  return result;
}

void MAbstractDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
  if ( objectiveType == (int)Searching ) searching( objectiveValue.toString() );
  if ( objectiveType == (int)Initiating ) initiating();
  if ( objectiveType == (int)Saving ) saving( objectiveValue.value<QObject *>() );
}
/*
 * End class definition: *[ MAbstractDBWrapper ]*
*/
