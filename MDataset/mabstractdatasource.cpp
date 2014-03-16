#include "mabstractdatasource.h"

#include "mabstractdbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDataSource ]*
*/
MAbstractDataSource::MAbstractDataSource(QObject *parent) :
  QObject(parent),
  m__Wrapper(NULL),
  m__SavedObjectIndex(-1)
{
  m__Founded = new MDataSourceModel( this );
  m__Founded->setSourceType( MAbstractDBWrapper::Founded );

  m__Initiated = new MDataSourceModel( this );
  m__Initiated->setSourceType( MAbstractDBWrapper::Initiated );

  m__Selected = new MDataSourceModel( this );
  m__Selected->setSourceType( MAbstractDBWrapper::Selected );
}

MAbstractDataSource::MAbstractDataSource( MAbstractDBWrapper *wrapper, QObject *parent ) :
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

  m__Selected = new MDataSourceModel( this );
  m__Selected->setSource( wrapper );
  m__Selected->setSourceType( MAbstractDBWrapper::Selected );
}

MAbstractDataSource::~MAbstractDataSource()
{
  m__Wrapper = NULL;

  delete m__Founded;
  m__Founded = NULL;

  delete m__Initiated;
  m__Initiated = NULL;

  delete m__Selected;
  m__Selected = NULL;
}

void MAbstractDataSource::findObject( const QString &filter )
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  if ( m__Wrapper->find( filter ) )
    emit statusChanged();
  else disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
}

void MAbstractDataSource::initiateObject()
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );
  if ( m__Wrapper->initiate() )
    emit statusChanged();
  else disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );
}

void MAbstractDataSource::selectObject( int indexInFounded )
{
  if ( m__Wrapper == NULL || !m__Wrapper->select( indexInFounded ) ) return;

  int index = m__Wrapper->count( (int)MAbstractDBWrapper::Selected )-1;
  m__Selected->insertObjects( index, index );
}

void MAbstractDataSource::saveObject( int indexInInitiated )
{
  if ( m__Wrapper == NULL ) return;

  connect( m__Wrapper, SIGNAL(finished()), this, SLOT(saveObjectFinished()) );
  m__SavedObjectIndex = indexInInitiated;
  if ( m__Wrapper->save( indexInInitiated ) )
    emit statusChanged();
  else disconnect( m__Wrapper, SIGNAL(finished()), this, SLOT(saveObjectFinished()) );
}

QString MAbstractDataSource::connectionName() const
{
  return m__Wrapper->connectionName();
}

void MAbstractDataSource::setConnectionName( const QString &connectionName )
{
  if ( m__Wrapper == NULL ) return;

  if ( !m__Wrapper->setConnectionName( connectionName ) ) return;

  emit connectionNameChanged();
}

int MAbstractDataSource::status() const
{
  if ( m__Wrapper == NULL || !m__Wrapper->isRunning() ) return Ready;

  return Loading;
}

MDataSourceModel * MAbstractDataSource::founded() const
{
  return m__Founded;
}

MDataSourceModel * MAbstractDataSource::initiated() const
{
  return m__Initiated;
}

MDataSourceModel * MAbstractDataSource::selected() const
{
  return m__Selected;
}

void MAbstractDataSource::setDBWrapper( MAbstractDBWrapper *wrapper )
{
  if ( m__Wrapper != NULL && m__Wrapper != wrapper )
  {
    m__Wrapper->terminate();
    m__Wrapper->wait();
  }
  m__Wrapper = wrapper;
  m__Founded->setSource( m__Wrapper );
  m__Initiated->setSource( m__Wrapper );
  m__Selected->setSource( m__Wrapper );
}

MAbstractDBWrapper * MAbstractDataSource::dbWrapper() const
{
  return m__Wrapper;
}

int MAbstractDataSource::savedObjectIndex() const
{
  return m__SavedObjectIndex;
}

void MAbstractDataSource::setSavedObjectIndex( int savedObjectIndex )
{
  m__SavedObjectIndex = savedObjectIndex;
}

/*
 * End class definition: *[ MDataSource ]*
*/
