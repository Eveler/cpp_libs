#include "mdocumentdatasource.h"

#include "mdocumentdbwrapper.h"
#include "mhumandbwrapper.h"
#include "morganizationdbwrapper.h"

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MDocumentDataSource ]*
*/
MDocumentDataSource::MDocumentDataSource(QObject *parent) :
  MAbstractDataSource(new MDocumentDBWrapper(), parent),
  m__SavedDocumentOwner(NULL),
  m__SavedDocument(NULL)
{
}

MDocumentDataSource::~MDocumentDataSource()
{
  //  qDebug() << __func__ << __LINE__;
    MAbstractDBWrapper *wrapper = dbWrapper();
    setDBWrapper( NULL );

  //  LogDebug() << wrapper;
    delete wrapper;
    wrapper = NULL;
}

void MDocumentDataSource::findObject( QObject *documentOwner, const QString &filter )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
  if ( wrapper->isRunning() ) return;
  if ( documentOwner == NULL ) return;
  if ( tr( documentOwner->metaObject()->className() ) == tr( "MHuman" ) )
  {
    MHuman *human = qobject_cast<MHuman *>( documentOwner );
    connect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
    if ( wrapper->find( human, filter ) ) emit statusChanged();
    else disconnect( wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  }
  else if ( tr( documentOwner->metaObject()->className() ) == tr( "MOrganization" ) )
  {
    MOrganization *organization = qobject_cast<MOrganization *>( documentOwner );
    connect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
    if ( wrapper->find( organization, filter ) ) emit statusChanged();
    else disconnect( wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  }
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
}

void MDocumentDataSource::saveObject( QObject *documentOwner, MDocument *document )
{
  //  qDebug() << metaObject()->className() << __func__ << __LINE__;
  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
  if ( wrapper->isRunning() ) return;
  if ( documentOwner == NULL || document == NULL ) return;
  if ( tr( documentOwner->metaObject()->className() ) != tr( "MHuman" ) &&
       tr( documentOwner->metaObject()->className() ) != tr( "MOrganization" ) )
    return;

  m__SavedDocumentOwner = documentOwner;
  m__SavedDocument = document;
  setSavedObjectIndex( wrapper->index( MAbstractDBWrapper::Initiated, document ) );
  connect( dbWrapper(), SIGNAL(finished()), this, SLOT(saveObjectFinished()) );
  if ( wrapper->save( m__SavedDocumentOwner, document ) ) emit statusChanged();
  else disconnect( wrapper, SIGNAL(finished()), this, SLOT(saveObjectFinished()) );
  //  qDebug() << metaObject()->className() << __func__ << __LINE__;
}


void MDocumentDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
//  qDebug() << metaObject()->className() << __func__ << __LINE__;

  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  QObject *firstSearched = wrapper->searched();
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  if ( firstSearched != NULL )
  {
//    qDebug() << firstSearched;
//    qDebug() << metaObject()->className() << __func__ << __LINE__;
    MDataSourceModel *model = qobject_cast<MDataSourceModel *>( firstSearched );
//    qDebug() << metaObject()->className() << __func__ << __LINE__;
//    qDebug() << model;
    model->resetModel();
  }
//  qDebug() << metaObject()->className() << __func__ << __LINE__;

  dbWrapper()->releaseOldResources();

//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  emit statusChanged();
}

void MDocumentDataSource::initiateObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  int index = dbWrapper()->count( (int)MAbstractDBWrapper::Initiated )-1;
  initiated()->insertObjects( index, index );

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MDocumentDataSource::saveObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(saveObjectFinished()) );

  int savedObjectIndex = this->savedObjectIndex();
  if ( savedObjectIndex != -1 )
  {
    if ( tr( m__SavedDocumentOwner->metaObject()->className() ) == tr( "MHuman" ) )
    {
      MHuman *human = qobject_cast<MHuman *>( m__SavedDocumentOwner );
      int index = human->documents()->index( m__SavedDocument );
      human->documents()->insertObjects( index, index );
    }
    if ( tr( m__SavedDocumentOwner->metaObject()->className() ) == tr( "MOrganization" ) )
    {
      MOrganization *organization = qobject_cast<MOrganization *>( m__SavedDocumentOwner );
      int index = organization->documents()->index( m__SavedDocument );
      organization->documents()->insertObjects( index, index );
    }

    this->setSavedObjectIndex( -1 );
    initiated()->removeObjects( savedObjectIndex, savedObjectIndex );
  }
  dbWrapper()->releaseOldResources();
  m__SavedDocumentOwner = NULL;
  m__SavedDocument = NULL;

  emit saved();
  emit statusChanged();
}
/*
 * End class definition: *[ MDocumentDataSource ]*
*/
