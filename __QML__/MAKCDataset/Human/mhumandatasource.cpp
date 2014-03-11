#include "mhumandatasource.h"

#include "mhumandbwrapper.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ MHumanDataSource ]*
*/
MHumanDataSource::MHumanDataSource(QObject *parent) :
  MDataSource(new MHumanDBWrapper(), parent)
{
}

MHumanDataSource::~MHumanDataSource()
{
//  qDebug() << __func__ << __LINE__;
  MAbstractDBWrapper *wrapper = dbWrapper();
  setDBWrapper( NULL );

//  qDebug() << __func__ << __LINE__ << wrapper;
  delete wrapper;
  wrapper = NULL;
}
/*
 * End class definition: *[ MHumanDataSource ]*
*/
