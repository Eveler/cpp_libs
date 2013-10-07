#include "abstractdocumentslist.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

AbstractDocumentsList::AbstractDocumentsList(const QVariant Id, QSqlDatabase db,
                                             QObject *parent) :
  QObject(parent),loader(NULL),saver(NULL),ownLoader(true),ownSaver(true),
  ID(Id),doclistModel(NULL),DB(db)
{
}

AbstractDocumentsList::~AbstractDocumentsList(){
  LogDebug()<<"~AbstractDocumentsList() BEGIN";
  if(ownLoader) if(loader) //loader->deleteLater();
    delete loader;
  if(ownSaver) if(saver) //saver->deleteLater();
    delete saver;
  LogDebug()<<"~AbstractDocumentsList() END";
}

void AbstractDocumentsList::setLoader(AbstractDocListLoader *l){
  if(!l || loader==l) return;
  if(loader) loader->disconnect(this);
  if(ownLoader) //loader->deleteLater();
    delete loader;
  loader=l;
  ownLoader=false;
  connect(l,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(l,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(l,SIGNAL(progress(qint64,qint64)),SIGNAL(progress(qint64,qint64)));
  connect(l,SIGNAL(done(bool)),SIGNAL(loadDone(bool)));
  connect(l,SIGNAL(documentLoadDone(MFCDocumentInfo*)),
          SIGNAL(documentLoadDone(MFCDocumentInfo*)));
  connect(l,SIGNAL(modelDestroyed()),SLOT(destroyModel()));
}

void AbstractDocumentsList::setSaver(AbstractDocListSaver *s){
  if(!s || saver==s) return;
  if(saver) saver->disconnect(this);
  if(ownSaver) //saver->deleteLater();
    delete saver;
  saver=s;
  ownSaver=false;
  connect(s,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(s,SIGNAL(error(QString)),SIGNAL(error(QString)));
//  connect(s,SIGNAL(progress(qint64,qint64)),SIGNAL(progress(qint64,qint64)));
  connect(s,SIGNAL(progress(qint64,qint64)),
          SLOT(showSaveProgress(qint64,qint64)));
  connect(s,SIGNAL(documentSaved(MFCDocumentInfo*,QVariant)),
          SLOT(setDocumentID(MFCDocumentInfo*,QVariant)));
}

QVariant AbstractDocumentsList::id() const{
  return ID;
}

void AbstractDocumentsList::clear(){
  if(loader) loader->clear();
}

QList< MFCDocumentInfo* > AbstractDocumentsList::findDocuments(QString doc_type,
                                                         QDate doc_date,
                                                         QString doc_number,
                                                         QString doc_series,
                                                         QString doc_name,
                                                         QString doc_agency,
                                                         QDateTime doc_created,
                                                         QDate doc_expires) const{
  // нужно возвращать сортированный список (как в модели)
  QList< MFCDocumentInfo* > list;
  foreach(MFCDocumentInfo *doc,doclistModel->documents()){
    bool found=false;

    if(doc->type()==doc_type && doc->date()==doc_date) found=true;
    if(found && !doc_number.isEmpty()) if(doc_number!=doc->number()) found=false;
    if(found && !doc_series.isEmpty()) if(doc_series!=doc->series()) found=false;
    if(found && !doc_name.isEmpty()) if(doc_name!=doc->name()) found=false;
    if(found && !doc_agency.isEmpty()) if(doc_agency!=doc->agency()) found=false;
    if(found && doc_created.isValid())
      if(doc_created!=doc->createDate()) found=false;
    if(found && doc_expires.isValid())
      if(doc_expires!=doc->expiresDate()) found=false;

    if(found) list<<doc;
  }

  return list;
}

void AbstractDocumentsList::cancelDownload(){
  if(loader) loader->cancelDownload();
}

bool AbstractDocumentsList::save(QSqlDatabase db, QString declar,
                                 QDateTime saveTime){
  bool res=true;
  res=saveDocuments(db,declar);
  if(!res) return res;
  return saveDocList(db,saveTime);
}

void AbstractDocumentsList::objectDestroyed(){
  if(loader==sender()) loader=NULL;
  else if(saver==sender()) saver=NULL;
}

void AbstractDocumentsList::setDocumentID(MFCDocumentInfo *doc, QVariant id){
  LogDebug()<<doc->type()<<"<- id ="<<id;
  doclistModel->setDocumentID(doc,id);
}

void AbstractDocumentsList::showSaveProgress(qint64 val, qint64 total){
  qint64 c=doclistModel->newDocuments().count()+1;
  qint64 t=(total>0?total:1)*c;
  qint64 v=1;
  foreach(MFCDocumentInfo *doc,doclistModel->newDocuments())
    if(!doc->url().isEmpty()) v++;
  v*=(val>0?val:t/c);
  emit progress(v,t);
}

void AbstractDocumentsList::destroyModel(){
//  emit modelDestroyed();
  doclistModel=NULL;
}
