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
  QList< MFCDocument* > docs=docListModel->documents();
  emit modelDestroyed();
//  LogDebug()<<"modelDestroyed";
  delete docListModel;
//  LogDebug()<<"model deleted";
  while(!docs.isEmpty()){
    MFCDocument *doc=docs.takeFirst();
    MFCDocument::remove(doc);
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
  connect(s,SIGNAL(dataTransferProgress(qint64,qint64,MFCDocument*)),
          SIGNAL(progress(qint64,qint64)));
  connect(s,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(s,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(s,SIGNAL(loaded(MFCDocument*)),SIGNAL(documentLoadDone(MFCDocument*)));
}

AbstractDocsStorage *AbstractDocListLoader::storage() const{
  return docStorage;
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

void AbstractDocListLoader::connectDocument2Loader(MFCDocument *doc){
  if(!doc || !docStorage) return;
  doc->disconnect(SIGNAL(needBody(QString,MFCDocument*)));
  connect(doc,SIGNAL(needBody(QString,MFCDocument*)),
          docStorage,SLOT(load(QString,MFCDocument*)),Qt::UniqueConnection);
}

void AbstractDocListLoader::setError(QString str){
  errStr=str;
  emit error(errStr);
}
