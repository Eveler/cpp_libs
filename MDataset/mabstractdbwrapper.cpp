#include "mabstractdbwrapper.h"

#include "mdatasource.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QUuid>
#include <QSqlDriver>


/*
 * Begin C++ class definition: *[ MAbstractDBWrapper ]*
*/
MAbstractDBWrapper::MAbstractDBWrapper( MDataSource *parent ) :
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
    object = NULL;
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
  m__Locker->unlock();
}

void MAbstractDBWrapper::setParent( MDataSource *parent )
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

bool MAbstractDBWrapper::find( const QString &filter )
{
  if ( isRunning() ) return false;

  locker()->lockForWrite();
  m__ObjectiveType = (int)Searching;
  m__ObjectiveValue.setValue( filter );
  locker()->unlock();

  start();
  return true;
}

bool MAbstractDBWrapper::initiate()
{
  if ( isRunning() ) return false;

  locker()->lockForWrite();
  m__ObjectiveType = (int)Initiating;
  locker()->unlock();

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
  pAppend( (int)Selected, object );
  locker()->unlock();

  return true;
}

bool MAbstractDBWrapper::save( int indexInInitiated )
{
  if ( isRunning() ) return false;

  locker()->lockForRead();
  QObject *object = pObject( (int)Initiated, indexInInitiated );
  locker()->unlock();
  if ( object == NULL ) return false;

  locker()->lockForWrite();
  m__ObjectiveType = (int)Saving;
  m__ObjectiveValue = QVariant::fromValue( object );
  locker()->unlock();

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

QReadWriteLock * MAbstractDBWrapper::locker() const
{
  return m__Locker;
}

void MAbstractDBWrapper::run()
{
  QPair<int, QVariant> objective = this->objective();
  job( objective.first, objective.second );
}

void MAbstractDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
  if ( objectiveType == (int)Searching ) searching( objectiveValue.toString() );
  if ( objectiveType == (int)Initiating ) initiating();
  if ( objectiveType == (int)Saving ) saving( objectiveValue.value<QObject *>() );
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
/*
 * End class definition: *[ MAbstractDBWrapper ]*
*/
