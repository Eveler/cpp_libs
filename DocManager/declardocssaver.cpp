#include <QSqlQuery>
#include <QSqlError>
#include "declardocssaver.h"
#include "ftpdocsstorage.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

DeclarDocsSaver::DeclarDocsSaver(QSqlDatabase db, QString id, QObject *parent) :
  AbstractDocListSaver(db,id,parent){
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
