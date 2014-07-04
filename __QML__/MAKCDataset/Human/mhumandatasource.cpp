#include "mhumandatasource.h"

#include "mhumandbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MHumanDataSource ]*
*/
MHumanDataSource::MHumanDataSource(QObject *parent) :
  MAbstractDataSource(new MHumanDBWrapper(), parent)
{
}

MHumanDataSource::~MHumanDataSource()
{
//  qDebug() << __func__ << __LINE__;
  MAbstractDBWrapper *wrapper = dbWrapper();
  setDBWrapper( NULL );

//  LogDebug() << wrapper;
  delete wrapper;
  wrapper = NULL;
}

void MHumanDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );

  if ( dbWrapper()->error().isNull() )  founded()->resetModel();
  else emit error( dbWrapper()->error() );

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MHumanDataSource::initiateObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  if ( dbWrapper()->error().isNull() )
  {
    int index = dbWrapper()->count( (int)MAbstractDBWrapper::Initiated )-1;
    initiated()->insertObjects( index, index );
  }
  else emit error( dbWrapper()->error() );

  dbWrapper()->releaseOldResources();

  emit statusChanged();
}

void MHumanDataSource::saveObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(saveObjectFinished()) );

  int index = savedObjectIndex();
  setSavedObjectIndex( -1 );

  if ( dbWrapper()->error().isNull() )
  {
    initiated()->removeObjects( index, index );

    index = dbWrapper()->count( (int)MAbstractDBWrapper::Founded )-1;
    founded()->insertObjects( index, index );
  }
  else emit error( dbWrapper()->error() );

  dbWrapper()->releaseOldResources();

  emit saved();
  emit statusChanged();
}
/*
 * End class definition: *[ MHumanDataSource ]*
*/
