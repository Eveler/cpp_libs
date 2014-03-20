#include "mdocumentdatasource.h"

#include "mdocumentdbwrapper.h"

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

void MDocumentDataSource::findObject( MHuman *human )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
  connect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
  if ( wrapper->find( human ) ) emit statusChanged();
  else disconnect( wrapper, SIGNAL(finished()), this, SLOT(findObjectFinished()) );
}

void MDocumentDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );
//  qDebug() << metaObject()->className() << __func__ << __LINE__;

  MDocumentDBWrapper *wrapper = qobject_cast<MDocumentDBWrapper *>( dbWrapper() );
  QObject *firstSearched = wrapper->searched();
  if ( firstSearched != NULL )
  {
    MDataSourceModel *model = qobject_cast<MDataSourceModel *>( firstSearched );
    model->resetModel();
  }

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MDocumentDataSource::initiateObjectFinished()
{

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MDocumentDataSource::saveObjectFinished()
{

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}
/*
 * End class definition: *[ MDocumentDataSource ]*
*/
