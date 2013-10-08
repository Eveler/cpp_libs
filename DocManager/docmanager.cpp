//#include <QApplication>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "docmanager.h"
#include "amslogger.h"
#include "ftpdocsstorage.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

Docmanager::Docmanager(QSqlDatabase db, QObject *parent) :
  QObject(parent),
  DB(db),
  allDocs(new DocumentsModel(this)),
  curClientDocs(NULL),
  loop(new QEventLoop(this)),
  /*stor(NULL),ownStorage(false),*/
  timer(new QTimer(this)),
  declarDocs(NULL),
  newDocs(new DocumentsModel(this)),
  curDocpathsDocs(NULL)
{
  allDocs->setObjectName("allDocs_model");
  newDocs->setObjectName("newDocs_model");
  timer->setInterval(10000);
  connect(timer,SIGNAL(timeout()),SLOT(timeout()));
  connect(this,SIGNAL(dataTransferProgress(qint64,qint64)),SLOT(updateTimer()));
}

Docmanager::~Docmanager(){
  //  LogDebug()<<"~Docmanager() BEGIN";
  clear();
  //  timer->deleteLater();
  delete timer;
  //  loop->deleteLater();
  delete loop;
  //  allDocs->deleteLater();
  QList< MFCDocumentInfo* > docs=allDocs->documents();
  delete allDocs;
  while(!docs.isEmpty()){
    MFCDocumentInfo *doc=docs.takeFirst();
    MFCDocumentInfo::remove(doc);
  }
  //  newDocs->deleteLater();
  docs=newDocs->documents();
  delete newDocs;
  while(!docs.isEmpty()){
    MFCDocumentInfo *doc=docs.takeFirst();
    MFCDocumentInfo::remove(doc);
  }
  //  LogDebug()<<"~Docmanager() END";
}

//void Docmanager::setDocumentsStorage(AbstractDocsStorage *storage){
//  if(!storage) return;
//  ownStorage=false;
//  stor=storage;
//  connect(stor,SIGNAL(dataTransferProgress(qint64,qint64,MFCDocument*)),
//          SIGNAL(dataTransferProgress(qint64,qint64)));
//  connect(stor,SIGNAL(destroyed()),SLOT(objectDestroyed()));
//  connect(stor,SIGNAL(error(QString)),SIGNAL(error(QString)));
//  connect(stor,SIGNAL(loaded(MFCDocument*)),SLOT(documentLoaded()));
//  connect(stor,SIGNAL(saved(QString)),SLOT(documentSaved(QString)));
//}

DocumentsModel *Docmanager::allDocuments() const{
  return allDocs;
}

DocumentsModel *Docmanager::addedDocuments() const{
  return newDocs;
}

QVariant Docmanager::currentClient() const{
  if(!curClientDocs) return QVariant();
  return curClientDocs->id();
}

MFCDocumentInfo *Docmanager::clientDocument(const QModelIndex &index) const{
  if(!curClientDocs) return NULL;
  QSortFilterProxyModel *model=
      qobject_cast< QSortFilterProxyModel* >(curClientDocs->model());
  if(!model) return NULL;
  QModelIndex idx=model->mapToSource(model->index(index.row(),index.column()));
  MFCDocumentInfo *doc=curClientDocs->documents()->document(idx);

  return doc;
}

DocumentsModel *Docmanager::clientDocuments() const{
  if(!curClientDocs) return NULL;
  if(!curClientDocs->documents()) curClientDocs->load(DB);
  return curClientDocs->documents();
}

QAbstractItemModel * Docmanager::sortedClientDocuments() const
{
  if(!curClientDocs) return NULL;
  if(!curClientDocs->documents()) curClientDocs->load(DB);
  return curClientDocs->model();
}

MFCDocumentInfo *Docmanager::docpathsDocument(const QModelIndex &index) const{
  if(!curDocpathsDocs) return NULL;
  QSortFilterProxyModel *model=
      qobject_cast< QSortFilterProxyModel* >(curDocpathsDocs->model());
  if(!model) return NULL;
  QModelIndex idx=model->mapToSource(model->index(index.row(),index.column()));
  MFCDocumentInfo *doc=curDocpathsDocs->documents()->document(idx);

  return doc;
}

DocumentsModel *Docmanager::docpathsDocuments() const{
  if(!curDocpathsDocs) return NULL;
  if(!curDocpathsDocs->documents()) curDocpathsDocs->load(DB);
  return curDocpathsDocs->documents();
}

QAbstractItemModel * Docmanager::sortedDocpathsDocuments() const
{
  if(!curDocpathsDocs) return NULL;
  if(!curDocpathsDocs->documents()) curDocpathsDocs->load(DB);
  return curDocpathsDocs->model();
}

MFCDocumentInfo *Docmanager::declarDocument(const QModelIndex &index) const{
  QSortFilterProxyModel *model=
      qobject_cast< QSortFilterProxyModel* >(declarDocs->model());
  if(!model) return NULL;
  QModelIndex idx=model->mapToSource(model->index(index.row(),index.column()));
  MFCDocumentInfo *doc=declarDocs->documents()->document(idx);

  return doc;
}

DocumentsModel *Docmanager::declarDocuments() const{
  if(!declarDocs) return NULL;
  if(!declarDocs->documents()) declarDocs->load(DB);
  return declarDocs->documents();
}

QAbstractItemModel * Docmanager::sortedDeclarDocuments() const
{
  if(!declarDocs) return NULL;
  if(!declarDocs->documents()) declarDocs->load(DB);
  return declarDocs->model();
}

void Docmanager::setSaveTime(QDateTime dt){
  saveTime=dt;
}

QSqlDatabase Docmanager::database() const{
  return DB;
}

bool Docmanager::addClient(QVariant id){
  if(id.isNull()) return false;
  if(clientsDocs.key(id,NULL)){
    setError(tr("Заявитель с ID=%1 уже добавлен").arg(id.toString()));
    return false;
  }

  ClientDocuments *cd=new ClientDocuments(id,DB,this);
  //  connect(cd,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
  connect(cd,SIGNAL(documentLoadDone(MFCDocumentInfo*)),SLOT(cancelDownload()));
  connect(cd,SIGNAL(documentLoadDone(MFCDocumentInfo*)),
          SIGNAL(documentLoadDone(MFCDocumentInfo*)));
  connect(cd,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(cd,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  clientsDocs.insert(cd,id);
  cd->load(DB);
  DocumentsModel *dm=cd->documents();
  if(!dm) return false;
  foreach(MFCDocumentInfo *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocumentInfo*)),
          SLOT(allDocsAdd(MFCDocumentInfo*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocumentInfo*)),
          SLOT(allDocsRemove(MFCDocumentInfo*)),Qt::UniqueConnection);

  if(!curClientDocs) setClientCurrent(id);

  return true;
}

void Docmanager::setClientCurrent(QVariant id){
  curClientDocs=clientsDocs.key(id,NULL);
  if(!curClientDocs && !id.isNull() && id!=0){
    setError(tr("Ошибка при установке заявителя ID=%1 "
                "текущим: заявитель не найден")
             .arg(id.toString()));
    return;
  }
  if(!id.isNull() && id!=0){
    emit currentClientChanged(curClientDocs->documents());
    emit currentClientChanged(curClientDocs->model());
    //    LogDebug()<<curClientDocs->model()->rowCount();
    emit currentClientChanged(id);
  }
}

void Docmanager::unsetCurrentClient(){
  curClientDocs=NULL;
}

void Docmanager::removeClient(QVariant id){
  if(id.isNull()) return;
  QMutableHashIterator< ClientDocuments*,QVariant > i(clientsDocs);
  while(i.hasNext()){
    i.next();
    if(i.value()==id){
      if(i.key()==curClientDocs) unsetCurrentClient();
      //      i.key()->disconnect(this);
      ClientDocuments *cd=i.key();
      //      i.key()->deleteLater();
      i.remove();
      DocumentsModel *dm=cd->documents();
      foreach(MFCDocumentInfo *doc,dm->documents()){
        dm->removeDocument(doc);
        MFCDocumentInfo::remove(doc);
      }
      delete cd;
    }
  }
}

bool Docmanager::removeClientDocument(MFCDocumentInfo *doc){
  if(!doc) return false;
  if(curClientDocs) return curClientDocs->documents()->removeDocument(doc);
  return false;
}

bool Docmanager::setDeclar(const QVariant id){
  if(id.isNull()) return false;

  unsetDeclar();

  declarDocs=new DeclarDocuments(id,DB,this);
  //  connect(declarDocs,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
  connect(declarDocs,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(declarDocs,SIGNAL(documentLoadDone(MFCDocumentInfo*)),
          SLOT(cancelDownload()));
  connect(declarDocs,SIGNAL(documentLoadDone(MFCDocumentInfo*)),
          SIGNAL(documentLoadDone(MFCDocumentInfo*)));
  connect(declarDocs,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(declarDocs,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  declarDocs->load(DB);
  DocumentsModel *dm=declarDocs->documents();
  if(!dm) return false;
  foreach(MFCDocumentInfo *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocumentInfo*)),
          SLOT(allDocsAdd(MFCDocumentInfo*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocumentInfo*)),
          SLOT(allDocsRemove(MFCDocumentInfo*)),Qt::UniqueConnection);

  emit declarSet(id);
  emit declarSet(declarDocs->model());
  emit declarSet(dm);

  return true;
}

void Docmanager::unsetDeclar(){
  if(declarDocs){
    //    declarDocs->deleteLater();
    DocumentsModel *dm=declarDocs->documents();
    foreach(MFCDocumentInfo *doc,dm->documents()){
      dm->removeDocument(doc);
      MFCDocumentInfo::remove(doc);
    }
    delete declarDocs;
    declarDocs=NULL;
  }
}

bool Docmanager::removeDeclarDocument(MFCDocumentInfo *doc){
  if(!doc) return false;
  if(declarDocs) return declarDocs->documents()->removeDocument(doc);
  return false;
}

bool Docmanager::addDocpaths(QVariant id){
  if(id.isNull()) return false;
  if(docpathsDocs.key(id,NULL)){
    setError(tr("Шаг с ID=%1 уже добавлен").arg(id.toString()));
    return false;
  }
  //  if(!declarDocs){
  //    setError(tr("Дело не определено!"));
  //    LogWarning()<<tr("Дело не определено!");
  //    return false;
  //  }

  DocpathsDocuments *dd=new DocpathsDocuments(id,DB,this);
  //  connect(dd,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
  connect(dd,SIGNAL(documentLoadDone(MFCDocumentInfo*)),SLOT(cancelDownload()));
  connect(dd,SIGNAL(documentLoadDone(MFCDocumentInfo*)),
          SIGNAL(documentLoadDone(MFCDocumentInfo*)));
  connect(dd,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(dd,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  docpathsDocs.insert(dd,id);
  dd->load(DB);
  DocumentsModel *dm=dd->documents();
  if(!dm) return false;
  foreach(MFCDocumentInfo *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocumentInfo*)),
          SLOT(allDocsAdd(MFCDocumentInfo*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocumentInfo*)),
          SLOT(allDocsRemove(MFCDocumentInfo*)),Qt::UniqueConnection);

  if(!curDocpathsDocs) setDocpathsCurrent(id);

  return true;
}

void Docmanager::unsetCurrentDocpaths(){
  curDocpathsDocs=NULL;
}

void Docmanager::removeDocpaths(QVariant id){
  if(id.isNull()) return;
  QMutableHashIterator< DocpathsDocuments*,QVariant > i(docpathsDocs);
  while(i.hasNext()){
    i.next();
    if(i.value()==id){
      if(i.key()==curDocpathsDocs) if(!nextDocpaths()) curDocpathsDocs=NULL;
      //      i.key()->disconnect();
      DocpathsDocuments *dd=i.key();
      //      i.key()->deleteLater();
      i.remove();
      DocumentsModel *dm=dd->documents();
      foreach(MFCDocumentInfo *doc,dm->documents()){
        dm->removeDocument(doc);
        MFCDocumentInfo::remove(doc);
      }
      delete dd;
    }
  }
}

void Docmanager::setDocpathsCurrent(QVariant id){
  curDocpathsDocs=docpathsDocs.key(id,NULL);
  if(!curDocpathsDocs && !id.isNull() && id!=0){
    setError(tr("Ошибка при установке шага ID=%1 "
                "текущим: шаг не найден")
             .arg(id.toString()));
    return;
  }
  if(!id.isNull() && id!=0){
    emit currentDocpathsChanged(curDocpathsDocs->documents());
    emit currentDocpathsChanged(curDocpathsDocs->model());
    //    LogDebug()<<curDocpathsDocs->model()->rowCount();
    emit currentDocpathsChanged(id);
  }
}

bool Docmanager::nextDocpaths(){
  if(docpathsDocs.count()==0) return false;
  if(!curDocpathsDocs) setDocpathsCurrent(docpathsDocs.begin().value());

  QHash< DocpathsDocuments*,QVariant >::const_iterator i=
      docpathsDocs.find(curDocpathsDocs);
  if(i==docpathsDocs.end()){
    setDocpathsCurrent(docpathsDocs.begin().value());
    return true;
  }else{
    ++i;
    if(i==docpathsDocs.end()){
      if(docpathsDocs.count()==1) return false;
      setDocpathsCurrent(docpathsDocs.begin().value());
    }else setDocpathsCurrent(i.value());
    return true;
  }
}

bool Docmanager::removeDocpathsDocument(MFCDocumentInfo *doc){
  if(!doc) return false;
  if(curDocpathsDocs) return curDocpathsDocs->documents()->removeDocument(doc);
  return false;
}

MFCDocumentInfo *Docmanager::newDocument(MFCDocumentInfo *doc){
  if(!doc) return doc;

  QVariant val=saveTime.isValid()?saveTime:QDateTime::currentDateTime();
  if(!doc->dynamicPropertyNames().contains(tr("Добавлен").toLocal8Bit()))
    doc->setProperty(tr("Добавлен").toLocal8Bit(),val);
  if(!doc->dynamicPropertyNames().contains(tr("Ответственный").toLocal8Bit()))
    doc->setProperty(tr("Ответственный").toLocal8Bit(),QVariant(QVariant::String));
  if(!doc->dynamicPropertyNames().contains("initial"))
    doc->setProperty("initial",QVariant(QVariant::Bool));

  if(declarDocs){
    DocumentsModel *dm=declarDocs->documents();
    if(!dm){
      declarDocs->load(DB);
      dm=declarDocs->documents();
    }
    LogDebug()<<"Adding to declarDocs";
    dm->addDocument(doc,documentID(doc));
  }

  if(curClientDocs){
    DocumentsModel *dm=curClientDocs->documents();
    if(!dm){
      curClientDocs->load(DB);
      dm=curClientDocs->documents();
    }
    LogDebug()<<"Adding to curClientDocs";
    dm->addDocument(doc,documentID(doc));
  }

  if(curDocpathsDocs){
    DocumentsModel *dm=curDocpathsDocs->documents();
    if(!dm){
      curDocpathsDocs->load(DB);
      dm=curDocpathsDocs->documents();
    }
    LogDebug()<<"Adding to curDocpathsDocs";
    dm->addDocument(doc,documentID(doc));
  }

  return doc;
}

bool Docmanager::loadDocument(MFCDocumentInfo *doc){
  if(!doc) return false;
  if(toAdd2All(doc)) return false;

  if( doc != NULL && ( doc->localFile().isEmpty() || !QFileInfo( doc->localFile() ).exists() ) )
  {
    if ( declarDocs->documents()->documents().contains( doc ) )
      declarDocs->load( doc );
    else if ( curClientDocs->documents()->documents().contains( doc ) )
      curClientDocs->load( doc );
    else return false;
    timer->start();
    return ( loop->exec() == 0 );
  }
  return true;
}

bool Docmanager::removeNewDocument(MFCDocumentInfo *doc){
  if(!doc) return false;

  if(newDocs->documents().contains(doc)){
    QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
    while(ci.hasNext()){
      ci.next();
      DocumentsModel *dm=ci.key()->documents();
      if(dm->isNew(doc)) dm->removeDocument(doc);
    }

    if(declarDocs && declarDocs->documents()->isNew(doc))
      declarDocs->documents()->removeDocument(doc);

    QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
    while(di.hasNext()){
      di.next();
      DocumentsModel *dm=di.key()->documents();
      if(dm->isNew(doc)) dm->removeDocument(doc);
    }

    newDocs->removeDocument(doc);
    return true;
  }

  return false;
}

bool Docmanager::save(QString declarNumber){
  bool res=saveDocuments(declarNumber);
  if(res) res=saveDocumentsLists();
  return res;
}

bool Docmanager::saveDocuments(QString declarNumber){
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }
  bool canTrans=DB.driver()->hasFeature(QSqlDriver::Transactions);
  if(canTrans)
    if(!DB.transaction()){
      setError(tr("Ошибка начала транзакции: %1").arg(DB.lastError().text()));
      return false;
    }
  // сохраняем документы из списков declarDocs, clientsDocs, docpathsDocs
  // сначала на ftp, затем в таблицу documents
  if(declarDocs){
    if(!declarDocs->saveDocuments(DB,declarNumber.isEmpty()?
                                  declarDocs->id().toString():declarNumber)){
      if(canTrans) DB.rollback();
      return false;
    }
  }

  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  if(ci.hasNext()) LogDebug()<<"Saving ClientDocuments";
  while(ci.hasNext()){
    ci.next();
    if(ci.key()){
      if(!ci.key()->saveDocuments(DB,declarDocs->id().toString())){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  if(di.hasNext()) LogDebug()<<"Saving DocpathsDocuments";
  while(di.hasNext()){
    di.next();
    if(di.key()){
      if(!di.key()->saveDocuments(DB,declarDocs->id().toString())){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  if(canTrans)
    if(!DB.commit()){
      setError(tr("Ошибка завершения транзакции: %1").arg(DB.lastError().text()));
      return false;
    }
  return true;
}

bool Docmanager::saveDocumentsLists(bool initial){
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }
  bool canTrans=DB.driver()->hasFeature(QSqlDriver::Transactions);
  if(canTrans)
    if(!DB.transaction()){
      setError(tr("Ошибка начала транзакции: %1").arg(DB.lastError().text()));
      return false;
    }
  // сохраняем документы из списков declarDocs, clientsDocs, docpathsDocs
  // соответственно в таблицы declars_documents,client_documents,
  // docpaths_documents
  if(declarDocs){
    LogDebug()<<"Saving declarDocsList";
    if(!declarDocs->saveDocList(DB,saveTime,initial)){
      if(canTrans) DB.rollback();
      return false;
    }
  }

  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  if(ci.hasNext()) LogDebug()<<"Saving clientsDocsList";
  while(ci.hasNext()){
    ci.next();
    if(ci.key()){
      if(!ci.key()->saveDocList(DB,saveTime)){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  if(di.hasNext()) LogDebug()<<"Saving docpathsDocsList";
  while(di.hasNext()){
    di.next();
    if(di.key()){
      if(!di.key()->saveDocList(DB,saveTime)){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  if(canTrans)
    if(!DB.commit()){
      setError(tr("Ошибка завершения транзакции: %1").arg(DB.lastError().text()));
      return false;
    }
  return true;
}

bool Docmanager::saveDeleteDocuments(){
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }
  bool canTrans=DB.driver()->hasFeature(QSqlDriver::Transactions);
  if(canTrans)
    if(!DB.transaction()){
      setError(tr("Ошибка начала транзакции: %1").arg(DB.lastError().text()));
      return false;
    }

  // Удаляем документы из списков declarDocs, clientsDocs, docpathsDocs
  // соответственно из таблиц declars_documents,client_documents,
  // docpaths_documents
  // Проверяем наличие документа хотя бы в одной из данных таблиц
  // Если отсутствует, удаляем документ из таблицы documents
  QStringList clients_ids;
  QStringList docpaths_ids;

  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  if(ci.hasNext()) LogDebug()<<"Deleting from clientsDocsList";
  while(ci.hasNext()){
    ci.next();
    if(ci.key()){
      QVariant clients_id=ci.key()->id();
      clients_ids<<clients_id.toString();
      if(!ci.key()->saveDeleteDocuments(DB)){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  if(di.hasNext()) LogDebug()<<"Deleting from docpathsDocsList";
  while(di.hasNext()){
    di.next();
    if(di.key()){
      QVariant docpaths_id=di.key()->id();
      docpaths_ids<<docpaths_id.toString();
      if(!di.key()->saveDeleteDocuments(DB)){
        if(canTrans) DB.rollback();
        return false;
      }
    }
  }

  if(declarDocs){
    LogDebug()<<"Deleting from declarDocsList";
    // Если документ есть в clients_documents или docpaths_documents, пропускаем
    declarDocs->set_clients_ids(clients_ids);
    declarDocs->set_docpaths_ids(docpaths_ids);
    if(!declarDocs->saveDeleteDocuments(DB)){
      if(canTrans) DB.rollback();
      return false;
    }
  }

  if(canTrans)
    if(!DB.commit()){
      setError(tr("Ошибка завершения транзакции: %1").arg(DB.lastError().text()));
      return false;
    }
  return true;
}

void Docmanager::clear(){
  errStr.clear();
  cancelDownload();

  curDocpathsDocs=NULL;
  QMutableHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  while(di.hasNext()){
    di.next();
    di.key()->disconnect(this);
    //    di.key()->deleteLater();
    DocpathsDocuments *dd=di.key();
    di.remove();
    DocumentsModel *dm=dd->documents();
    if ( dm != NULL )
    {
      foreach(MFCDocumentInfo *doc,dm->documents()){
        //      dm->removeDocument(doc);
        MFCDocumentInfo::remove(doc);
      }
    }
    delete dd;
  }
  docpathsDocs.clear();

  curClientDocs=NULL;
  QMutableHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  while(ci.hasNext()){
    ci.next();
    ci.key()->disconnect(this);
    //    ci.key()->deleteLater();
    ClientDocuments *cd=ci.key();
    ci.remove();
    DocumentsModel *dm=cd->documents();
    if ( dm != NULL )
    {
      foreach(MFCDocumentInfo *doc,dm->documents()){
        //      dm->removeDocument(doc);
        MFCDocumentInfo::remove(doc);
      }
    }
    delete cd;
  }
  clientsDocs.clear();

  if(declarDocs)
  {
    declarDocs->disconnect(this);
    //    declarDocs->deleteLater();
    DocumentsModel *dm=declarDocs->documents();
    if ( dm != NULL )
    {
      foreach(MFCDocumentInfo *doc,dm->documents()){
        //      dm->removeDocument(doc);
        MFCDocumentInfo::remove(doc);
      }
    }
    delete declarDocs;
    declarDocs=NULL;
  }

  foreach(MFCDocumentInfo *doc,allDocs->documents()){
    //    allDocs->removeDocument(doc);
    MFCDocumentInfo::remove(doc);
  }
  allDocs->clear();
  foreach(MFCDocumentInfo *doc,newDocs->documents()){
    //    newDocs->removeDocument(doc);
    MFCDocumentInfo::remove(doc);
  }
  newDocs->clear();
}

void Docmanager::cancelDownload(){
  AbstractDocumentsList *docList=
      qobject_cast< AbstractDocumentsList* >(sender());
  if(docList) docList->cancelDownload();
  else{
    if(declarDocs) declarDocs->cancelDownload();
    QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
    while(ci.hasNext()){
      ci.next();
      ci.key()->cancelDownload();
    }
    QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
    while(di.hasNext()){
      di.next();
      di.key()->cancelDownload();
    }
  }
  //  if(stor) stor->cancel();
  if(timer->isActive()) timer->stop();
  loop->quit();
}

void Docmanager::allDocsAdd(MFCDocumentInfo *doc){
  if(!doc) return;
  DocumentsModel *model=qobject_cast< DocumentsModel* >(sender());
  if(!model) return;

  if(model->isNew(doc)){
    if(newDocs->documents().contains(doc)) return;
    newDocs->addDocument(doc,model->documentID(doc),true);
    LogDebug()<<doc->type()<<"added as new";
    emit documentAdded(newDocs);
  }

  if(!toAdd2All(doc)) return;
  allDocs->addDocument(doc,model->documentID(doc),model->isNew(doc));
  LogDebug()<<doc->type()<<"added to all";
}

void Docmanager::allDocsRemove(MFCDocumentInfo *doc){
  //  LogDebug()<<"allDocsRemove(MFCDocumentInfo*) BEGIN";
  if(!doc) return;
  //  LogDebug()<<"doc="<<doc;
  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  while(di.hasNext()){
    di.next();
    if(declarDocs && !declarDocs->documents()->documents().contains(doc))
      di.key()->documents()->removeDocument(doc);
    else if(di.key()->documents()->documents().contains(doc)){
      //      LogDebug()<<"allDocsRemove("<<doc<<") END";
      return;
    }
  }
  if(declarDocs && sender()!=declarDocs && !doc->property("initial").toBool() &&
     toAdd2All(doc)){
    LogDebug()<<"remove from declarDocs:"<<doc<<doc->type()
             <<"id ="<<documentID(doc);
    declarDocs->documents()->removeDocument(doc);
  }
  if(!allDocs->isNew(doc) && declarDocs &&
     declarDocs->documents()->documents().contains(doc)){
    //    LogDebug()<<"allDocsRemove("<<doc<<") END";
    return;
  }
  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  while(ci.hasNext()){
    ci.next();
    if(ci.key()->documents()->documents().contains(doc)){
      //      LogDebug()<<"allDocsRemove("<<doc<<") END";
      return;
    }
  }

  if(allDocs->documents().contains(doc)) allDocs->removeDocument(doc);
  if(newDocs->documents().contains(doc)) newDocs->removeDocument(doc);
  MFCDocumentInfo::remove(doc);
  //  LogDebug()<<"allDocsRemove("<<doc<<") END";
}

void Docmanager::set_error(QString str,QString file,int line){
  errStr=tr("%1 (%2): %3").arg(file).arg(line).arg(str);
  emit error(errStr);
}

void Docmanager::objectDestroyed(){
  if(sender()==declarDocs) declarDocs=NULL;
}

void Docmanager::timeout(){
  cancelDownload();
  setError(tr("Время ожидания загрузки истекло"));
}

void Docmanager::updateTimer(){
  if(timer->isActive()) timer->start();
  //  timer->start();
}

QVariant Docmanager::documentID(MFCDocumentInfo *doc) const{
  if(!doc) return QVariant();

  if(declarDocs){
    if(!declarDocs->documents()) declarDocs->load(DB);
    DocumentsModel *dm=declarDocs->documents();
    if(dm->documents().contains(doc)){
      QVariant id=dm->documentID(doc);
      if(!id.isNull()) return id;
    }
  }

  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  while(ci.hasNext()){
    ci.next();
    if(!ci.key()->documents()) ci.key()->load(DB);
    DocumentsModel *dm=ci.key()->documents();
    if(dm->documents().contains(doc)){
      QVariant id=dm->documentID(doc);
      if(!id.isNull()) return id;
    }
  }

  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  while(di.hasNext()){
    di.next();
    if(!di.key()->documents()) di.key()->load(DB);
    DocumentsModel *dm=di.key()->documents();
    if(dm->documents().contains(doc)){
      QVariant id=dm->documentID(doc);
      if(!id.isNull()) return id;
    }
  }

  return QVariant();
}

bool Docmanager::toAdd2All(MFCDocumentInfo *doc) const{
  //  LogDebug()<<"toAdd2All(MFCDocumentInfo*) BEGIN";
  if(!doc) return false;
  //  LogDebug()<<"doc="<<doc;
  bool toAdd=false;
  if(!allDocs->documents().contains(doc)){
    toAdd=true;
    QString type=doc->type();
    QDate date=doc->date();
    QDateTime created=doc->createDate();
    QString number=doc->number();
    QString series=doc->series();
    QString name=doc->name();
    foreach(MFCDocumentInfo *d,allDocs->documents())
      if(d->type()==type && d->date()==date && d->createDate()==created
         && d->number()==number && d->series()==series && d->name()==name){
        toAdd=false;
        break;
      }
  }
  //  LogDebug()<<"toAdd2All("<<doc<<") END";
  return toAdd;
}
