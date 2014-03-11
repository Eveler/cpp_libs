#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include "declardocsloader.h"
#include "ftpdocsstorage.h"
#include "amslogger.h"

DeclarDocsLoader::DeclarDocsLoader(QSqlDatabase db,QObject *parent) :
  AbstractDocListLoader(db,parent){
}

DeclarDocsLoader::~DeclarDocsLoader(){
//  LogDebug()<<"~DeclarDocsLoader() BEGIN";
//  LogDebug()<<"~DeclarDocsLoader() END";
}

DocumentsModel *DeclarDocsLoader::load(QVariant foreignID){
//  LogDebug()<<Q_FUNC_INFO<<"BEGIN: param ="<<foreignID;
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
                    "  d.created,d.url,dd.documents_id,d.doctype_id,"
                    "  dd.added AS \"Добавлен\","
                    "  user_name_initials(dd.responsible) AS \"Ответственный\","
                    "  dd.initial "
                    " FROM declar_documents dd,documents d,doctypes dt "
                    " WHERE dd.declars_id=%1 "
                    "  AND dd.documents_id=d.id AND d.doctype_id=dt.id"
                    " ORDER BY d.id,d.created DESC,dd.added DESC")
      .arg(foreignID.toString());
  QSqlQuery qry(DB);
  if(!qry.exec(strQry)){
    setError(tr("Ошибка загрузки списка документов для дела ID=%1: %2: QUERY: %3")
             .arg(foreignID.toString()).arg(qry.lastError().text())
             .arg(qry.lastQuery()));
    return NULL;
  }
  QStringList skipNames;
  skipNames<<"id"<<"documents_id"<<"doctype_id";
  while(qry.next()){
    MFCDocumentInfo *doc=NULL;
    QVariant docId = qry.record().value("documents_id");
    foreach(MFCDocumentInfo *d,docListModel->documents()){
      if( docListModel->documentID( d ).toString() == docId.toString() )
      {
        doc=d;
        break;
      }
    }
    if(!doc){
      doc=MFCDocumentInfo::instance(
            qry.record().field("type").value().toString(),
            qry.record().field("name").value().toString(),
            qry.record().field("series").value().toString(),
            qry.record().field("number").value().toString(),
            qry.record().field("date").value().toDate(),
            qry.record().field("expires").value().toDate(),
            qry.record().field("agency").value().toString(),
            qry.record().field("created").value().toDateTime() );
//      doc->setProperty("created_in",tr("%1 (%2)").arg(__FILE__).arg(__LINE__));
      doc->setUrl( qry.record().field("url").value().toString() );
      doc->setInitial( qry.record().field( "initial" ).value().toBool() );

      for(int f=0;f<qry.record().count();f++){
        if(skipNames.contains(qry.record().fieldName(f))) continue;
        doc->setProperty(qry.record().fieldName(f).toLocal8Bit(),qry.value(f));
      }

      QSqlQuery subQry(DB);
      strQry = tr( "SELECT original_number, original_pages, copy_number, copy_pages"
                   " WHERE documents_id=%1 ORDER BY id DESC LIMIT 1" ).arg( docId.toString() );
      if ( subQry.exec( strQry ) && subQry.next() )
      {
        doc->setOriginalExemplars( qry.record().field("original_number").value().toInt() );
        doc->setOriginalPages( qry.record().field("original_pages").value().toInt() );
        doc->setCopyExemplars( qry.record().field("copy_number").value().toInt() );
        doc->setCopyPages( qry.record().field("copy_pages").value().toInt() );
      }

      docListModel->addDocument( doc, docId, false );
    }
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
  }

//  LogDebug()<<Q_FUNC_INFO<<"END";
  return docListModel;
}
