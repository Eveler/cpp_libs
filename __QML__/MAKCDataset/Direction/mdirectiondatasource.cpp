#include "mdirectiondatasource.h"

#include "mdirectiondbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDoctypeDataSource ]*
*/
MDirectionDataSource::MDirectionDataSource(QObject *parent) :
  MAbstractDataSource(new MDirectionDBWrapper(), parent)
{
}

MDirectionDataSource::~MDirectionDataSource()
{
  //  qDebug() << __func__ << __LINE__;
    MAbstractDBWrapper *wrapper = dbWrapper();
    setDBWrapper( NULL );

  //  LogDebug() << wrapper;
    delete wrapper;
    wrapper = NULL;
}

void MDirectionDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );

  founded()->resetModel();

  emit statusChanged();
}

void MDirectionDataSource::initiateObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  int index = dbWrapper()->count( (int)MAbstractDBWrapper::Initiated )-1;
  initiated()->insertObjects( index, index );

  emit statusChanged();
}

void MDirectionDataSource::saveObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(saveObjectFinished()) );

  int index = dbWrapper()->count( MAbstractDBWrapper::Selected )-1;
  selected()->insertObjects( index, index );

  index = savedObjectIndex();
  setSavedObjectIndex( -1 );
  initiated()->removeObjects( index, index );

  emit saved();
  emit statusChanged();
}
/*
 * End class definition: *[ MDirectionDataSource ]*
*/
