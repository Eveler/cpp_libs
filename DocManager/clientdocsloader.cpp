#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include "clientdocsloader.h"
#include "ftpdocsstorage.h"
#include "amslogger.h"

ClientDocsLoader::ClientDocsLoader(QSqlDatabase db,
                                   QObject *parent) :
  AbstractDocListLoader(db,parent){
}

ClientDocsLoader::~ClientDocsLoader(){
  LogDebug()<<"~ClientDocsLoader() BEGIN";
  LogDebug()<<"~ClientDocsLoader() END";
}

DocumentsModel *ClientDocsLoader::load(QVariant foreignID){
  if(foreignID.isNull()) return NULL;
  if(!DB.isValid()){
    setError(tr("Указано ошибочное подключение к базе данных"));
    return NULL;
  }
  if(!DB.isOpen()) if(!DB.open()){
    setError(tr("Ошибка подключения к базе данных: %1")
             .arg(DB.lastError().text()));
    return NULL;
  }
  // если docStorage ещё не задан создаём ftpStorage
  if(!docStorage){
    setStorage(&FtpDocsStorage::addStorage(
                 foreignID.toString()+"__"+
                 metaObject()->className()+"_ftp_storage"));
    docStorage->connectToHost(DB.userName(),DB.password(),DB.hostName(),21);
    ownStorage=true;
  }

  QString strQry=tr("SELECT DISTINCT d.id,dt.aname AS type,d.docname AS name,"
                    "  d.docseries AS series,d.docnum AS number,"
                    "  d.docdate AS date,d.expires,"
                    "  (SELECT name FROM docagency WHERE cod=d.docagency_id) "
                    "    AS agency,"
                    "  d.created,d.url,cd.documents_id,d.doctype_id,"
                    "  cd.added AS \"Добавлен\","
                    "  user_name_initials(cd.responsible) AS \"Ответственный\" "
                    "FROM client_documents cd,documents d,doctypes dt "
                    "WHERE cd.clients_id=%1 "
//                    "  AND (d.expires>=now()::date OR d.expires IS NULL) "
                    "  AND cd.documents_id=d.id AND d.doctype_id=dt.id "
                    "ORDER BY d.created DESC")
      .arg(foreignID.toString());
  QSqlQuery qry(DB);
  if(!qry.exec(strQry)){
    setError(tr("Ошибка загрузки списка документов для заявителя ID=%1: %2: QUERY: %3")
             .arg(foreignID.toString()).arg(qry.lastError().text())
             .arg(qry.lastQuery()));
    return NULL;
  }
  QStringList skipNames;
  skipNames<<"id"<<"documents_id"<<"doctype_id";
  while(qry.next()){
    MFCDocument *doc=MFCDocument::instance(
          qry.record().field("type").value().toString(),
          qry.record().field("date").value().toDate(),
          qry.record().field("created").value().toDateTime(),this);
    connectDocument2Loader(doc);
//    connect(doc,SIGNAL(needBody(QString,MFCDocument*)),
//            docStorage,SLOT(load(QString,MFCDocument*)));

//    doc->setAgency(qry.record().value("agency").toString());
//    doc->setCreateDate(qry.record().value("created").toDateTime());
//    doc->setDate(qry.record().value("docdate").toDate());
//    doc->setExpiresDate(qry.record().value("expires").toDate());
//    doc->setName(qry.record().value("docname").toString());
//    doc->setNumber(qry.record().value("docnum").toString());
//    doc->setSeries(qry.record().value("docseries").toString());
//    doc->setType(qry.record().value("aname").toString());
//    doc->setUrl(qry.record().value("url").toString());
    for(int f=0;f<qry.record().count();f++){
      if(skipNames.contains(qry.record().fieldName(f))) continue;
      doc->setProperty(qry.record().fieldName(f).toLocal8Bit(),qry.value(f));
    }
    doc->setProperty("initial",QVariant(QVariant::Bool));

    docListModel->addDocument(doc,qry.record().value("documents_id"),false);
  }

  return docListModel;
}
