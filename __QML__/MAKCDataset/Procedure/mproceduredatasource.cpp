#include "mproceduredatasource.h"

#include "mproceduredbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MDoctypeDataSource ]*
*/
MProcedureDataSource::MProcedureDataSource(QObject *parent) :
  MAbstractDataSource(new MProcedureDBWrapper(), parent)
{
}

MProcedureDataSource::~MProcedureDataSource()
{
  //  qDebug() << __func__ << __LINE__;
    MAbstractDBWrapper *wrapper = dbWrapper();
    setDBWrapper( NULL );

  //  LogDebug() << wrapper;
    delete wrapper;
    wrapper = NULL;
}

void MProcedureDataSource::findObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(findObjectFinished()) );

  founded()->resetModel();

  emit statusChanged();
}

void MProcedureDataSource::initiateObjectFinished()
{
  disconnect( dbWrapper(), SIGNAL(finished()), this, SLOT(initiateObjectFinished()) );

  int index = dbWrapper()->count( (int)MAbstractDBWrapper::Initiated )-1;
  initiated()->insertObjects( index, index );

  emit statusChanged();
}

void MProcedureDataSource::saveObjectFinished()
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
 * End class definition: *[ MProcedureDataSource ]*
*/
