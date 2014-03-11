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

void MAbstractDBWrapper::find( const QString &filter )
{
  if ( isRunning() ) return;

  locker()->lockForWrite();
  m__ObjectiveType = Searching;
  m__ObjectiveValue.setValue( filter );
  locker()->unlock();

  start();
}

void MAbstractDBWrapper::initiate()
{
  if ( isRunning() ) return;

  locker()->lockForWrite();
  m__ObjectiveType = Initiating;
  locker()->unlock();

  start();
}

void MAbstractDBWrapper::save( QObject *object )
{
  if ( isRunning() ) return;

  locker()->lockForWrite();
  m__ObjectiveType = Saving;
  m__ObjectiveValue = QVariant::fromValue( object );
  locker()->unlock();

  start();
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
  job();
}

void MAbstractDBWrapper::job()
{
  QPair<JobType, QVariant> objective = this->objective();
  if ( objective.first == Searching ) searching( objective.second.toString() );
  if ( objective.first == Initiating ) initiating();
  if ( objective.first == Saving ) saving( objective.second.value<QObject *>() );
}

QPair<MAbstractDBWrapper::JobType, QVariant> MAbstractDBWrapper::objective()
{
  locker()->lockForRead();
  QPair<JobType, QVariant> result = qMakePair( m__ObjectiveType, m__ObjectiveValue );
  m__ObjectiveType = None;
  m__ObjectiveValue.clear();
  locker()->unlock();

  return result;
}
/*
 * End class definition: *[ MAbstractDBWrapper ]*
*/
