#include "mdocumentdatasource.h"


MDocumentDataSource::MDocumentDataSource(QObject *parent) :
  MAbstractDataSource(parent)
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

void MDocumentDataSource::findObjectFinished()
{

}

void MDocumentDataSource::initiateObjectFinished()
{

}

void MDocumentDataSource::saveObjectFinished()
{

}

