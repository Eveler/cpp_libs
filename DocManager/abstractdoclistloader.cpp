#include <QUuid>
#include "abstractdoclistloader.h"
#include "amslogger.h"

AbstractDocListLoader::AbstractDocListLoader(QSqlDatabase db,
                                             QObject *parent) :
  QObject(parent),DB(db),docStorage(NULL),ownStorage(true){
  docListModel=new DocumentsModel(this);
}

AbstractDocListLoader::~AbstractDocListLoader(){
  LogDebug()<<"~AbstractDocListLoader() BEGIN";
//  docListModel->deleteLater();
  QList< MFCDocumentInfo* > docs=docListModel->documents();
  emit modelDestroyed();
//  LogDebug()<<"modelDestroyed";
  delete docListModel;
//  LogDebug()<<"model deleted";
  while(!docs.isEmpty()){
    MFCDocumentInfo *doc=docs.takeFirst();
    MFCDocumentInfo::remove(doc);
  }
//  LogDebug()<<"model documents deleted";
  if(docStorage) docStorage->disconnect(this);
  if(ownStorage){
    if(docStorage) docStorage->removeStorage();
  }
  docStorage=NULL;
  LogDebug()<<"~AbstractDocListLoader() END";
}

void AbstractDocListLoader::setStorage(AbstractDocsStorage *s){
  if(docStorage) docStorage->disconnect(this);
  if(ownStorage){
    if(docStorage) docStorage->removeStorage();
  }
  docStorage=s;
  ownStorage=false;
  connect(s,SIGNAL(dataTransferProgress(qint64,qint64,MFCDocumentInfo*)),
          SIGNAL(progress(qint64,qint64)));
  connect(s,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(s,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(s,SIGNAL(loaded(MFCDocumentInfo*)),SIGNAL(documentLoadDone(MFCDocumentInfo*)));
}

AbstractDocsStorage *AbstractDocListLoader::storage() const{
  return docStorage;
}

bool AbstractDocListLoader::load( MFCDocumentInfo *doc ) const
{
  if ( docStorage == NULL || !docListModel->documents().contains( doc ) ) return false;

  return docStorage->load( doc );
}

void AbstractDocListLoader::clear(){
  errStr.clear();
  docListModel->clear();
}

void AbstractDocListLoader::cancelDownload(){
  if(docStorage) docStorage->cancel();
}

void AbstractDocListLoader::objectDestroyed(){
  if(docStorage==sender()) docStorage=NULL;
}

void AbstractDocListLoader::setError(QString str){
  LogDebug() << __func__ << str;
  errStr=str;
  emit error(errStr);
}

void AbstractDocListLoader::beginAddDocuments()
{
  docListModel->beginAddDocuments();
}

void AbstractDocListLoader::endAddDocuments()
{
  docListModel->endAddDocuments();
}
