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

  // ���� docStorage ��� �� ����� ������ ftpStorage
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
  LogDebug()<<"ClientDocsSaver: saving list for"<<
              docList->newDocuments().count()<<"docs";
  foreach(MFCDocument *doc,docList->newDocuments())
    if(docList->documentID(doc).isNull()){
      QString doc_series=doc->series();
      setError(tr("����������� ID � ��������� '%1'%2%3 �� %4")
               .arg(doc->type())
               .arg(doc_series.isEmpty()?"":tr(" ���. ")+doc_series)
               .arg(doc->number().isEmpty()?"":tr(" � ")+doc->number())
               .arg(doc->date().toString("dd.MM.yyyy")));
      return false;
    }

  Q_UNUSED(initial);

  QDateTime time=(saveTime.isNull()?QDateTime::currentDateTime():saveTime);
  QSqlQuery qry(DB);
  QString qryStr="INSERT INTO client_documents "
      "(clients_id,documents_id,added) VALUES (?,?,?)";
  if(!qry.prepare(qryStr)){
    setError(tr("������ ���������� ���������� ������ ���������� ���������: %1 "
                "QUERY: %2").arg(qry.lastError().text()).arg(qryStr));
    return false;
  }
  foreach(MFCDocument *doc,docList->newDocuments()){
    LogDebug()<<"adding to list"<<doc->type()<<"id ="<<docList->documentID(doc);
    qry.addBindValue(foreign_id);
    qry.addBindValue(docList->documentID(doc));
    qry.addBindValue(time);
    if(!qry.exec()){
      setError(tr("������ ���������� ��������� ���������: %1 "
                  "QUERY: %2").arg(qry.lastError().text()).arg(qry.lastQuery()));
      return false;
    }
  }

  return true;
}
