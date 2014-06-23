#include "mdocumentdatasource.h"

#include "mdocumentdbwrapper.h"
#include "mhumandbwrapper.h"
#include "morganizationdbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDocumentDataSource ]*
*/
MDocumentDataSource::MDocumentDataSource(QObject *parent) :
  MAbstractDataSource(new MDocumentDBWrapper(), parent)
{
}

MDocumentDataSource::~MDocumentDataSource()
{
  //  qDebug() << __func__ << __LINE__;
    MAbstractDBWrapper *wrapper = dbWrapper();
    setDBWrapper( NULL );

  //  qDebug() << __func__ << __LINE__ << wrapper;
    delete wrapper;
    wrapper = NULL;
}

void MDocumentDataSource::findObject( QObject *documentOwner )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
  if ( wrapper->isRunning() ) return;
  if ( documentOwner == NULL ) return;
  if ( tr( documentOwner->metaObject()->className() ) == tr( "MHuman" ) )
  {
    MHuman *human = qobject_cast<MHuman *>( documentOwner );
    connect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
    if ( wrapper->find( human ) ) emit statusChanged();
    else disconnect( wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  }
  else if ( tr( documentOwner->metaObject()->className() ) == tr( "MOrganization" ) )
  {
    MOrganization *organization = qobject_cast<MOrganization *>( documentOwner );
    connect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
    if ( wrapper->find( organization ) ) emit statusChanged();
    else disconnect( wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  }
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
  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MDocumentDataSource::saveObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(saveObjectFinished()) );

  int savedObjectIndex = this->savedObjectIndex();
  if ( savedObjectIndex != -1 )
  {
    this->setSavedObjectIndex( -1 );
    initiated()->removeObjects( savedObjectIndex, savedObjectIndex );
  }
  dbWrapper()->releaseOldResources();

  emit saved();
  emit statusChanged();
}
/*
 * End class definition: *[ MDocumentDataSource ]*
*/
