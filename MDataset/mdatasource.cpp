#include "mdatasource.h"

#include "mabstractdbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDataSource ]*
*/
MDataSource::MDataSource(QObject *parent) :
  QObject(parent),
  m__Wrapper(NULL),
  m__SavedObjectIndex(-1)
{
  m__Founded = new MDataSourceModel( this );
  m__Founded->setSourceType( MAbstractDBWrapper::Founded );

  m__Initiated = new MDataSourceModel( this );
  m__Initiated->setSourceType( MAbstractDBWrapper::Initiated );
}

MDataSource::MDataSource( MAbstractDBWrapper *wrapper, QObject *parent ) :
  QObject(parent),
  m__SavedObjectIndex(-1)
{
  m__Wrapper = wrapper;
  m__Wrapper->setParent( this );

  m__Founded = new MDataSourceModel( this );
  m__Founded->setSource( wrapper );
  m__Founded->setSourceType( MAbstractDBWrapper::Founded );

  m__Initiated = new MDataSourceModel( this );
  m__Initiated->setSource( wrapper );
  m__Initiated->setSourceType( MAbstractDBWrapper::Initiated );
}

MDataSource::~MDataSource()
{
  m__Wrapper = NULL;

  delete m__Founded;
  m__Founded = NULL;

  delete m__Initiated;
  m__Initiated = NULL;
}

void MDataSource::findObject( const QString &filter )
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  m__Wrapper->find( filter );
  emit statusChanged();
}

void MDataSource::initiateObject()
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );
  m__Wrapper->initiate();
  emit statusChanged();
}

void MDataSource::saveObject( QObject *object )
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(saveObjectFinished()) );
  m__SavedObjectIndex = m__Wrapper->index( MAbstractDBWrapper::Initiated, object );
  m__Wrapper->save( object );
  emit statusChanged();
}

QString MDataSource::connectionName() const
{
  return m__Wrapper->connectionName();
}

void MDataSource::setConnectionName( const QString &connectionName )
{
  if ( m__Wrapper == NULL ) return;

  if ( !m__Wrapper->setConnectionName( connectionName ) ) return;

  emit connectionNameChanged();
}

int MDataSource::status() const
{
  if ( m__Wrapper == NULL || !m__Wrapper->isRunning() ) return Ready;

  return Loading;
}

MDataSourceModel * MDataSource::founded() const
{
  return m__Founded;
}

MDataSourceModel * MDataSource::initiated() const
{
  return m__Initiated;
}

void MDataSource::setDBWrapper( MAbstractDBWrapper *wrapper )
{
  if ( m__Wrapper != NULL && m__Wrapper != wrapper )
  {
    m__Wrapper->terminate();
    m__Wrapper->wait();
  }
  m__Wrapper = wrapper;
  m__Founded->setSource( m__Wrapper );
  m__Initiated->setSource( m__Wrapper );
}

MAbstractDBWrapper * MDataSource::dbWrapper() const
{
  return m__Wrapper;
}

void MDataSource::findObjectFinished()
{
  disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );

  m__Founded->resetModel();

  emit statusChanged();
}

void MDataSource::initiateObjectFinished()
{
  disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  int index = m__Wrapper->count( (int)MAbstractDBWrapper::Initiated )-1;
  m__Initiated->insertObjects( index, index );

  emit statusChanged();
}

void MDataSource::saveObjectFinished()
{
  disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(saveObjectFinished()) );

  int index = m__SavedObjectIndex;
  m__SavedObjectIndex = -1;
  if ( index > -1 )
    m__Initiated->removeObjects( index, index );

  emit saved();
  emit statusChanged();
}
/*
 * End class definition: *[ MDataSource ]*
*/
