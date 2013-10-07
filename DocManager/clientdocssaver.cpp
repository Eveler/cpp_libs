#include <QSqlQuery>
#include <QSqlError>
#include "clientdocssaver.h"
#include "ftpdocsstorage.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

ClientDocsSaver::ClientDocsSaver(QSqlDatabase db, QString id, QObject *parent) :
  AbstractDocListSaver(db,id,parent)
{
}

bool ClientDocsSaver::saveDocuments(DocumentsModel *docList, QString declar){
  if(!docList) return false;
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }

  // если docStorage ещё не задан создаём ftpStorage
  if(!docStorage){
    setStorage(&FtpDocsStorage::addStorage(
                 foreign_id+"__"+
                 metaObject()->className()+"_ftp_storage"));
    docStorage->connectToHost(DB.userName(),DB.password(),DB.hostName(),21);
    ownStorage=true;
  }
  return AbstractDocListSaver::saveDocuments(docList,declar);
}

bool ClientDocsSaver::saveDocList(DocumentsModel *docList, QDateTime saveTime,
                                  bool initial){
  if(!docList) return false;
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }
  LogDebug()<<"ClientDocsSaver: saving list for"<<
              docList->newDocuments().count()<<"docs";
  foreach(MFCDocumentInfo *doc,docList->newDocuments())
    if(docList->documentID(doc).isNull()){
      QString doc_series=doc->series();
      setError(tr("Отсутствует ID у документа '%1'%2%3 от %4")
               .arg(doc->type())
               .arg(doc_series.isEmpty()?"":tr(" сер. ")+doc_series)
               .arg(doc->number().isEmpty()?"":tr(" № ")+doc->number())
               .arg(doc->date().toString("dd.MM.yyyy")));
      return false;
    }

  Q_UNUSED(initial);

  QDateTime time=(saveTime.isNull()?QDateTime::currentDateTime():saveTime);
  QSqlQuery qry(DB);
  QString qryStr="INSERT INTO client_documents "
      "(clients_id,documents_id,added) VALUES (?,?,?)";
  if(!qry.prepare(qryStr)){
    setError(tr("Ошибка подготовки сохранения списка документов заявителя: %1 "
                "QUERY: %2").arg(qry.lastError().text()).arg(qryStr));
    return false;
  }
  foreach(MFCDocumentInfo *doc,docList->newDocuments()){
    LogDebug()<<"adding to list"<<doc->type()<<"id ="<<docList->documentID(doc);
    qry.addBindValue(foreign_id);
    qry.addBindValue(docList->documentID(doc));
    qry.addBindValue(time);
    if(!qry.exec()){
      setError(tr("Ошибка сохранения документа заявителя: %1 "
                  "QUERY: %2").arg(qry.lastError().text()).arg(qry.lastQuery()));
      return false;
    }
  }

  return true;
}

bool ClientDocsSaver::saveDeleteDocuments(DocumentsModel *docList){
  if(!docList) return false;
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return false;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return false;
  }
  QSqlQuery qry(DB);
  LogDebug()<<"ClientDocsSaver: deleting"<<
              docList->removedDocumentsIDs().count()<<"docs";
  foreach(QVariant id,docList->removedDocumentsIDs()){
    LogDebug()<<"clients_id ="<<foreign_id<<"documents_id ="<<id;
    QString qryStr=tr("DELETE FROM client_documents WHERE clients_id=%1"
                      " AND documents_id=%2")
        .arg(foreign_id)
        .arg(id.toString());
    if(!qry.exec(qryStr)){
      setError(tr("Ошибка удаления документа заявителя: %1 QUERY: %2")
               .arg(qry.lastError().text()).arg(qryStr));
      return false;
    }
    if(!removeFromDocuments(id.toString())) return false;
  }
  return true;
}
