#include <QApplication>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "docmanager.h"
#include "amslogger.h"
#include "ftpdocsstorage.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

Docmanager::Docmanager(QSqlDatabase db, QObject *parent) :
  QObject(parent),DB(db),allDocs(new DocumentsModel(this)),curClientDocs(NULL),
  loop(new QEventLoop(this)),/*stor(NULL),ownStorage(false),*/
  timer(new QTimer(this)),declarDocs(NULL),newDocs(new DocumentsModel(this)),
  curDocpathsDocs(NULL){
  timer->setInterval(5000);
  connect(timer,SIGNAL(timeout()),SLOT(timeout()));
  connect(this,SIGNAL(dataTransferProgress(qint64,qint64)),SLOT(updateTimer()));
}

Docmanager::~Docmanager(){
  LogDebug()<<"~Docmanager() BEGIN";
  timer->deleteLater();
  loop->deleteLater();
  clear();
  allDocs->deleteLater();
  newDocs->deleteLater();
//  if(ownStorage) stor->removeStorage();
  LogDebug()<<"~Docmanager() END";
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

MFCDocument *Docmanager::clientDocument(const QModelIndex &index) const{
  if(!curClientDocs) return NULL;
  QSortFilterProxyModel *model=
      qobject_cast< QSortFilterProxyModel* >(curClientDocs->model());
  if(!model) return NULL;
  QModelIndex idx=model->mapToSource(model->index(index.row(),index.column()));
  MFCDocument *doc=curClientDocs->documents()->document(idx);

  if(doc && !doc->isValid()){
//    if(!stor){
//      FtpDocsStorage *s=&FtpDocsStorage::addStorage("Docmanager_ftp_storage");
//      setDocumentsStorage(s);
//      if(!stor){
//        setError(tr("Ошибка при установке загрузчика документов: %1")
//                 .arg(FtpDocsStorage::errorString()));
//        return NULL;
//      }
//      s->setDataBaseName(DB.databaseName());
//      ownStorage=true;
//      //        stor=s;
//    }

//    if(!stor->connectToHost(DB.userName(),DB.password(),DB.hostName(),
//                            stor->port())){
//      //      setError(tr("Ошибка соединения с сервером: %1").arg(stor->errorString()));
//      return NULL;
//    }
//    if(!stor->load(doc->url(),doc)) return NULL;
//    //    }

    // запустим таймер для проверки загрузки на предмет зависания
    timer->start();
    loop->exec();
  }

  return doc;
}

DocumentsModel *Docmanager::clientDocuments() const{
  if(!curClientDocs) return NULL;
  if(!curClientDocs->documents()) curClientDocs->load(DB);
  return curClientDocs->documents();
}

DocumentsModel *Docmanager::docpathsDocuments() const{
  if(!curDocpathsDocs) return NULL;
  if(!curDocpathsDocs->documents()) curDocpathsDocs->load(DB);
  return curDocpathsDocs->documents();
}

DocumentsModel *Docmanager::declarDocuments() const{
  if(!declarDocs) return NULL;
  if(!declarDocs->documents()) declarDocs->load(DB);
  return declarDocs->documents();
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
  connect(cd,SIGNAL(documentLoadDone(MFCDocument*)),SLOT(cancelDownload()));
  connect(cd,SIGNAL(documentLoadDone(MFCDocument*)),
          SIGNAL(documentLoadDone(MFCDocument*)));
  connect(cd,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(cd,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  clientsDocs.insert(cd,id);
  cd->load(DB);
  DocumentsModel *dm=cd->documents();
  if(!dm) return false;
  foreach(MFCDocument *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocument*)),
          SLOT(allDocsAdd(MFCDocument*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocument*)),
          SLOT(allDocsRemove(MFCDocument*)),Qt::UniqueConnection);

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
    emit currentClientChanged(curClientDocs);
    emit currentClientChanged(curClientDocs->model());
    LogDebug()<<curClientDocs->model()->rowCount();
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
//      i.key()->disconnect();
      i.key()->deleteLater();
      i.remove();
    }
  }
}

bool Docmanager::setDeclar(const QVariant id){
  if(id.isNull()) return false;

  unsetDeclar();

  declarDocs=new DeclarDocuments(id,DB,this);
  connect(declarDocs,SIGNAL(documentLoadDone(MFCDocument*)),
          SLOT(cancelDownload()));
  connect(declarDocs,SIGNAL(documentLoadDone(MFCDocument*)),
          SIGNAL(documentLoadDone(MFCDocument*)));
  connect(declarDocs,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(declarDocs,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  declarDocs->load(DB);
  DocumentsModel *dm=declarDocs->documents();
  if(!dm) return false;
  foreach(MFCDocument *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocument*)),
          SLOT(allDocsAdd(MFCDocument*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocument*)),
          SLOT(allDocsRemove(MFCDocument*)),Qt::UniqueConnection);

  return true;

}

void Docmanager::unsetDeclar(){
  if(declarDocs){
    declarDocs->deleteLater();
    declarDocs=NULL;
  }
}

bool Docmanager::addDocpaths(QVariant id){
  if(id.isNull()) return false;
  if(docpathsDocs.key(id,NULL)){
    setError(tr("Шаг с ID=%1 уже добавлен").arg(id.toString()));
    return false;
  }

  DocpathsDocuments *dd=new DocpathsDocuments(id,DB,this);
  connect(dd,SIGNAL(documentLoadDone(MFCDocument*)),SLOT(cancelDownload()));
  connect(dd,SIGNAL(documentLoadDone(MFCDocument*)),
          SIGNAL(documentLoadDone(MFCDocument*)));
  connect(dd,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(dd,SIGNAL(progress(qint64,qint64)),
          SIGNAL(dataTransferProgress(qint64,qint64)));
  docpathsDocs.insert(dd,id);
  dd->load(DB);
  DocumentsModel *dm=dd->documents();
  if(!dm) return false;
  foreach(MFCDocument *doc,dm->documents()){
    if(toAdd2All(doc))
      allDocs->addDocument(doc,dm->documentID(doc),dm->isNew(doc));
  }
  connect(dm,SIGNAL(documentAdded(MFCDocument*)),
          SLOT(allDocsAdd(MFCDocument*)),Qt::UniqueConnection);
  connect(dm,SIGNAL(documentRemoved(MFCDocument*)),
          SLOT(allDocsRemove(MFCDocument*)),Qt::UniqueConnection);

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
      i.key()->deleteLater();
      i.remove();
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
    emit currentDocpathsChanged(curDocpathsDocs);
    emit currentDocpathsChanged(curDocpathsDocs->model());
    LogDebug()<<curDocpathsDocs->model()->rowCount();
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

MFCDocument *Docmanager::newDocument(MFCDocument *doc){
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

bool Docmanager::loadDocument(MFCDocument *doc){
  if(!doc) return false;
  if(toAdd2All(doc)) return false;

  if(!doc->isValid()){
    timer->start();
    loop->exec();
  }
  return doc->isValid();
}

bool Docmanager::save(QString declarNumber){
  bool res=saveDocuments(declarNumber);
  if(res) res=saveDocumentsLists();
  return res;
}

bool Docmanager::saveDocuments(QString declarNumber){
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
  QSqlQuery qry(DB);
  QString qryStr;
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

  if(declarDocs){
    declarDocs->disconnect();
    declarDocs->deleteLater();
    declarDocs=NULL;
  }

  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  while(ci.hasNext()){
    ci.next();
    ci.key()->disconnect();
    ci.key()->deleteLater();
  }
  clientsDocs.clear();
  curClientDocs=NULL;

  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  while(di.hasNext()){
    di.next();
    di.key()->disconnect();
    di.key()->deleteLater();
  }
  docpathsDocs.clear();
  curDocpathsDocs=NULL;

  allDocs->clear();
  newDocs->clear();
}

void Docmanager::cancelDownload(){
  AbstractDocumentsList *docList=
      qobject_cast< AbstractDocumentsList* >(sender());
  if(docList) docList->cancelDownload();
//  if(stor) stor->cancel();
  if(timer->isActive()) timer->stop();
  loop->quit();
}

void Docmanager::allDocsAdd(MFCDocument *doc){
  if(!doc) return;
  DocumentsModel *model=qobject_cast< DocumentsModel* >(sender());
  if(!model) return;

  if(model->isNew(doc)){
    if(newDocs->documents().contains(doc)) return;
    newDocs->addDocument(doc,model->documentID(doc),true);
    LogDebug()<<"HERE"<<doc->type()<<"added as new";
    emit documentAdded(newDocs);
  }

  if(!toAdd2All(doc)) return;
  allDocs->addDocument(doc,model->documentID(doc),model->isNew(doc));
  LogDebug()<<doc->type()<<"added to all";
}

void Docmanager::allDocsRemove(MFCDocument *doc){
  QHashIterator< ClientDocuments*,QVariant > ci(clientsDocs);
  while(ci.hasNext()){
    ci.next();
    if(ci.key()->documents()->documents().contains(doc)) return;
  }
  QHashIterator< DocpathsDocuments*,QVariant > di(docpathsDocs);
  while(di.hasNext()){
    di.next();
    if(di.key()->documents()->documents().contains(doc)) return;
  }
  if(!doc->property("initial").toBool() && declarDocs && sender()!=declarDocs)
    declarDocs->documents()->removeDocument(doc);
  if(!allDocs->isNew(doc) && declarDocs &&
     declarDocs->documents()->documents().contains(doc)) return;

  if(allDocs->documents().contains(doc)) allDocs->removeDocument(doc);
  if(newDocs->documents().contains(doc)) newDocs->removeDocument(doc);
}

void Docmanager::set_error(QString str,QString file,int line){
  errStr=tr("%1 (%2): %3").arg(file).arg(line).arg(str);
  emit error(errStr);
}

void Docmanager::objectDestroyed(){
//  if(sender()==stor) stor=NULL;
}

void Docmanager::timeout(){
  cancelDownload();
  setError(tr("Время ожидания загрузки истекло"));
}

void Docmanager::updateTimer(){
  if(timer->isActive()) timer->stop();
  timer->start();
}

QVariant Docmanager::documentID(MFCDocument *doc) const{
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

bool Docmanager::toAdd2All(MFCDocument *doc) const{
  bool toAdd=false;
  if(!allDocs->documents().contains(doc)){
    toAdd=true;
    QString type=doc->type();
    QDate date=doc->date();
    QDateTime created=doc->createDate();
    foreach(MFCDocument *d,allDocs->documents())
      if(d->type()==type && d->date()==date && d->createDate()==created){
        toAdd=false;
        break;
      }
  }
  return toAdd;
}
