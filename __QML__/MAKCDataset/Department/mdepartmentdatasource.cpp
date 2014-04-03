#include "mdepartmentdatasource.h"

#include "mdepartmentdbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDoctypeDataSource ]*
*/
MDepartmentDataSource::MDepartmentDataSource(QObject *parent) :
  MAbstractDataSource(new MDepartmentDBWrapper(), parent)
{
}

MDepartmentDataSource::~MDepartmentDataSource()
{
  //  qDebug() << __func__ << __LINE__;
    MAbstractDBWrapper *wrapper = dbWrapper();
    setDBWrapper( NULL );

  //  qDebug() << __func__ << __LINE__ << wrapper;
    delete wrapper;
    wrapper = NULL;
}

void MDepartmentDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );

  founded()->resetModel();

  emit statusChanged();
}

void MDepartmentDataSource::initiateObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  int index = dbWrapper()->count( (int)MAbstractDBWrapper::Initiated )-1;
  initiated()->insertObjects( index, index );

  emit statusChanged();
}

void MDepartmentDataSource::saveObjectFinished()
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
 * End class definition: *[ MDepartmentDataSource ]*
*/
