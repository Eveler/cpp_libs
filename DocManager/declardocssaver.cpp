#include <QSqlQuery>
#include <QSqlError>
#include "declardocssaver.h"
#include "ftpdocsstorage.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

DeclarDocsSaver::DeclarDocsSaver(QSqlDatabase db, QString id, QObject *parent) :
  AbstractDocListSaver(db,id,parent){
}

void DeclarDocsSaver::set_clients_ids(QStringList& ids){
  clients_ids=ids;
}

void DeclarDocsSaver::set_docpaths_ids(QStringList& ids){
  docpaths_ids=ids;
}

bool DeclarDocsSaver::saveDocuments(DocumentsModel *docList, QString declar){
  if(!docList) return false;

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

bool DeclarDocsSaver::saveDocList(DocumentsModel *docList,
                                  QDateTime saveTime, bool initial){
  if(!docList) return false;
  LogDebug()<<"DeclarDocsSaver: saving list for"<<
              docList->newDocuments().count()<<"docs";
  foreach(MFCDocument *doc,docList->newDocuments())
    if(docList->documentID(doc).isNull()){
      QString doc_series=doc->series();
      setError(tr("Отсутствует ID у документа '%1'%2%3 от %4")
               .arg(doc->type())
               .arg(doc_series.isEmpty()?"":tr(" сер. ")+doc_series)
               .arg(doc->number().isEmpty()?"":tr(" № ")+doc->number())
               .arg(doc->date().toString("dd.MM.yyyy")));
      return false;
    }

  QDateTime time=(saveTime.isNull()?QDateTime::currentDateTime():saveTime);
  QSqlQuery qry(DB);
  QString qryStr="INSERT INTO declar_documents "
      "(declars_id,documents_id,added,initial) VALUES (?,?,?,?)";
  if(!qry.prepare(qryStr)){
    setError(tr("Ошибка подготовки сохранения списка документов дела: %1 "
                "QUERY: %2").arg(qry.lastError().text()).arg(qryStr));
    return false;
  }
  foreach(MFCDocument *doc,docList->newDocuments()){
    LogDebug()<<"adding to list"<<doc->type()<<"id ="<<docList->documentID(doc);
    qry.addBindValue(foreign_id);
    qry.addBindValue(docList->documentID(doc));
    qry.addBindValue(time);
    qry.addBindValue(initial);
    if(!qry.exec()){
      setError(tr("Ошибка сохранения документа дела: %1 "
                  "QUERY: %2").arg(qry.lastError().text()).arg(qry.lastQuery()));
      return false;
    }
  }

  return true;
}

bool DeclarDocsSaver::saveDeleteDocuments(DocumentsModel *docList){
  if(!docList) return false;
  QString qryStr;
  QSqlQuery qry(DB);
  LogDebug()<<"DeclarDocsSaver: deleting"<<
              docList->removedDocumentsIDs().count()<<"docs";
  foreach(QVariant id,docList->removedDocumentsIDs()){
    if(clients_ids.count()>0)
      qryStr=tr("SELECT id FROM client_documents WHERE documents_id=%1"
                " AND clients_id in (%2) ")
          .arg(id.toString()).arg(clients_ids.join(","));
    // NOTE: maybe we can to not take into account documents where initial=false for removal them?
    if(docpaths_ids.count()>0)
      qryStr+=(qryStr.length()>0?"UNION ":"")+
          tr("SELECT id FROM docpaths_documents "
             "WHERE documents_id=%1 AND docpaths_id in (%2)")
          .arg(id.toString()).arg(docpaths_ids.join(","));
    if(!qry.exec(qryStr)){
      setError(tr("Ошибка получения информации о документе: %1 QUERY: %2")
               .arg(qry.lastError().text()).arg(qryStr));
      return false;
    }
    qry.next();
    if(qry.size()<1){
      qry.clear();
      LogDebug()<<"declars_id ="<<foreign_id<<"documents_id ="<<id;
      qryStr=tr("DELETE FROM declar_documents WHERE declars_id=%1"
                        " AND documents_id=%2")
          .arg(foreign_id)
          .arg(id.toString());
      if(!qry.exec(qryStr)){
        setError(tr("Ошибка удаления документа из дела: %1 QUERY: %2")
                 .arg(qry.lastError().text()).arg(qryStr));
        return false;
      }
      if(!removeFromDocuments(id.toString())) return false;
    }
  }
  return true;
}
