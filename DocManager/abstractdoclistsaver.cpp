#include <QSqlQuery>
#include <QSqlError>
#include "abstractdoclistsaver.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

AbstractDocListSaver::AbstractDocListSaver(QSqlDatabase db, QString id,
                                           QObject *parent) :
  QObject(parent),DB(db),docStorage(NULL),ownStorage(true),
  loop(new QEventLoop(this)),timer(new QTimer(this)),curDoc(NULL),foreign_id(id){
  timer->setInterval(10000);
  connect(timer,SIGNAL(timeout()),SLOT(storTimeout()));
}

AbstractDocListSaver::~AbstractDocListSaver(){
//  LogDebug()<<"~AbstractDocListSaver() BEGIN";
  if(docStorage) docStorage->disconnect(this);
  if(ownStorage){
    if(docStorage) docStorage->removeStorage();
  }
//  loop->deleteLater();
  delete loop;
//  timer->deleteLater();
  delete timer;
//  LogDebug()<<"~AbstractDocListSaver() END";
}

void AbstractDocListSaver::setStorage(AbstractDocsStorage *s){
  if(docStorage) docStorage->disconnect(this);
  if(ownStorage){
    if(docStorage) docStorage->removeStorage();
  }
  docStorage=s;
  ownStorage=false;
  connect(s,SIGNAL(dataTransferProgress(qint64,qint64,MFCDocumentInfo*)),
          SLOT(dataTransferProgress(qint64,qint64)));
  connect(s,SIGNAL(destroyed()),SLOT(objectDestroyed()));
  connect(s,SIGNAL(error(QString)),SIGNAL(error(QString)));
  connect(s,SIGNAL(saved(QString)),SLOT(documentSaveDone(QString)));
}

AbstractDocsStorage *AbstractDocListSaver::storage() const{
  return docStorage;
}

bool AbstractDocListSaver::saveDocuments(DocumentsModel *docList,
                                         QString declar){
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

  LogDebug()<<"Saving"<<docList->newDocuments().count()<<"documents";
  foreach(MFCDocumentInfo *doc,docList->newDocuments()){
    LogDebug()<<"Saving:"<<doc->type();
    QVariant docID=docList->documentID(doc);
    // проверим наличие документа в базе
    if(!doc->url().isEmpty()){
      QSqlQuery qry(DB);
      QString sqlStr=tr("SELECT d.id FROM documents d WHERE d.url='%1'")
          .arg(doc->url());
      if(!qry.exec(sqlStr)){
        setError(tr("Ошибка поиска документов в БД: %1 QUERY: %2")
                 .arg(qry.lastError().text())
                 .arg(qry.lastQuery()));
        return false;
      }
      if(!docID.isNull() && qry.size()>0){
        qry.clear();
        continue;
      }

      QString doc_name=doc->name();
      QString doc_series=doc->series();
      QString doc_agency=doc->agency();
      sqlStr="SELECT d.id,d.created,d.url FROM documents d "
          "WHERE d.doctype_id=(SELECT dt.id FROM doctypes dt WHERE dt.aname=%1)"
          " AND d.docname%2 AND d.docseries%3 AND d.docnum=%4 AND d.docdate=%5"
          " AND d.docagency_id%6";
      sqlStr=sqlStr.arg("'"+doc->type()+"'")
          .arg(doc_name.isNull()?" IS NULL":"='"+doc_name+"'")
          .arg(doc_series.isNull()?" IS NULL":"='"+doc_series+"'")
          .arg("'"+doc->number()+"'")
          .arg("'"+doc->date().toString("dd.MM.yyyy")+"'")
          .arg(doc_agency.isEmpty()?
                 " IS NULL":
                 "=(SELECT da.cod FROM docagency da WHERE da.\"name\"='"+
                 doc_agency+"')");
      if(!qry.exec(sqlStr)){
        setError(tr("Ошибка поиска документов в БД: %1 QUERY: %2")
                 .arg(qry.lastError().text())
                 .arg(qry.lastQuery()));
        return false;
      }

//      LogDebug()<<qry.executedQuery();

      if(qry.size()>0 && qry.next() && !docID.isNull()){
//        LogDebug()<<"docID ="<<docID<<"qry.value ="<<qry.value(0)<<
//                    "type ="<<doc->type()<<"created ="<<doc->createDate()<<
//                    qry.value(1);
        if(qry.value(0)!=docID && qry.value(1).toDateTime()==doc->createDate()){
          setError(tr("В БД найден дубликат документа '%1'%2%3 от %4, ID=%5")
                   .arg(doc->type())
                   .arg(doc_series.isEmpty()?"":tr(" сер. ")+doc_series)
                   .arg(doc->number().isEmpty()?"":tr(" № ")+doc->number())
                   .arg(doc->date().toString("dd.MM.yyyy"))
                   .arg(qry.value(0).toString()));
          return false;
        }else{// пропускаем выгрузку на ftp существующего документа
          LogWarning()<<tr("Posible document dublicate: DB id=%1, prog id=%2, "
                           "DB url=%3, prog url=%4").arg(qry.value(0).toString())
                        .arg(docID.toString())
                        .arg(qry.value(2).toString()).arg(doc->url());
          qry.clear();
          continue;
        }
      }
    }

    curDoc=doc;
    if ( !doc->localFile().isEmpty() )
    {
      bool res=docStorage->save(doc,declar);
      if(!res) return false;
      timer->start();
      if( curDoc && loop->exec() != 0 ) return false;
    }
    else
    {
      QVariant id = saveDocumentToDatabase( curDoc );
      curDoc = NULL;
      if ( id.isNull() ) return false;
      else emit documentSaved( doc, id );
    }
  }

  return true;
}

void AbstractDocListSaver::clear(){
  errStr.clear();
  curDoc=NULL;
}

void AbstractDocListSaver::cancelUpload(){
  if(docStorage) docStorage->cancel();
  curDoc=NULL;
}

void AbstractDocListSaver::objectDestroyed(){
  if(docStorage==sender()) docStorage=NULL;
  curDoc=NULL;
}

QVariant AbstractDocListSaver::saveDocumentToDatabase( MFCDocumentInfo *doc, const QString &path )
{
  if( doc == NULL )
  {
    setError(tr("Документ пуст"));
    return QVariant();
  }

  QSqlQuery qry(DB);

  QString qryStr=tr("SELECT id FROM doctypes WHERE aname='%1'")
      .arg(doc->type());
  if(!qry.exec(qryStr)){
    setError(tr("Ошибка запроса типа документа: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return QVariant();
  }
  if(!qry.next()){
    setError(tr("Неизвестная ошибка запроса: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return QVariant();
  }
  QVariant doctype_id=qry.value(0);
  qry.clear();

  QVariant docagency_id(QVariant::Int);
  if(!doc->agency().isEmpty()){
    qryStr=tr("SELECT cod FROM docagency WHERE \"name\"='%1'")
        .arg(doc->agency());
    if(!qry.exec(qryStr)){
      setError(tr("Ошибка запроса выдающей организации: %1 QUERY: %2")
               .arg(qry.lastError().text()).arg(qry.lastQuery()));
      return QVariant();
    }
    if(!qry.next()){
      setError(tr("Неизвестная ошибка запроса: %1 QUERY: %2")
               .arg(qry.lastError().text()).arg(qry.lastQuery()));
      return QVariant();
    }
    docagency_id=qry.value(0);
    qry.clear();
  }

  if(!qry.exec("SELECT nextval('documents_id_seq')")){
    setError(tr("Ошибка запроса ID документа: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return QVariant();
  }
  if(!qry.next()){
    setError(tr("Неизвестная ошибка запроса: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return QVariant();
  }
  QVariant id=qry.value(0);
  qry.clear();

  qryStr="INSERT INTO documents (id,doctype_id,docname,docseries,"
      "docnum,docdate,expires,docagency_id,url) VALUES (?,?,?,?,?,?,?,?,?)";
  if(!qry.prepare(qryStr)){
    setError(tr("Ошибка подготовки запроса сохранения документа: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qryStr));
    return QVariant();
  }
  qry.addBindValue(id);
  qry.addBindValue(doctype_id);
  qry.addBindValue(doc->name());
  qry.addBindValue(doc->series());
  qry.addBindValue(doc->number());
  qry.addBindValue(doc->date());
  qry.addBindValue(doc->expiresDate());
  qry.addBindValue(docagency_id);
  qry.addBindValue(path);
  if(!qry.exec()){
    setError(tr("Ошибка сохранения документа в БД: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return QVariant();
  }
  doc->setUrl(path);

  /*Сохраняем document_metadata************************************************/
  QList< QByteArray > pn=doc->dynamicPropertyNames();
  if(pn.contains(tr("Страниц").toLocal8Bit())
     || pn.contains(tr("Оригиналов").toLocal8Bit())
     || pn.contains(tr("Копий").toLocal8Bit())){
    qryStr="INSERT INTO document_metadata (documents_id,original_number,"
        "copy_number,original_pages,copy_pages) VALUES (%1,%2,%3,%4,%5)";
    qryStr=qryStr.arg(id.toString());
    qryStr=qryStr.arg( doc->originalExemplars() );
    qryStr=qryStr.arg( doc->copyExemplars() );
    qryStr=qryStr.arg( doc->originalPages() );
    qryStr=qryStr.arg( doc->copyPages() );
    if(!qry.exec(qryStr)){
      setError(tr("Ошибка сохранения метаданных документа в БД: %1 \nQUERY: %2")
               .arg(qry.lastError().text()).arg(qry.lastQuery()));
      return QVariant();
    }
  }
  /************************************************Сохраняем document_metadata*/
  return id;
}

void AbstractDocListSaver::documentSaveDone(QString path){
  if(path.isEmpty()){
    setError(tr("Путь документа пуст"));
    curDoc=NULL;
    loop->exit(-1);
    return;
  }

  QVariant id = saveDocumentToDatabase( curDoc, path );

  if ( !id.isNull() ) emit documentSaved(curDoc,id);
  curDoc=NULL;
  timer->stop();

  if ( !id.isNull() ) loop->quit();
  else loop->exit(-1);
}

void AbstractDocListSaver::storTimeout(){
  docStorage->cancel();
  setError(tr("Истекло время ожидания при передаче документа"));
  curDoc=NULL;
  loop->exit(-1);
}

void AbstractDocListSaver::dataTransferProgress(qint64 bytesDone,
                                                qint64 bytesTotal){
//  timer->stop();
  timer->start();
  emit progress(bytesDone,bytesTotal);
}

void AbstractDocListSaver::set_error(QString str, QString file, int line){
  errStr=tr("%1 (%2): %3").arg(file).arg(line).arg(str);
  LogDebug()<<errStr;
  timer->stop();
  curDoc=NULL;
  loop->exit(-1);
  emit error(errStr);
}

bool AbstractDocListSaver::removeFromDocuments(QString id){
  QSqlQuery qry(DB);
  QString qryStr=tr("SELECT id FROM client_documents WHERE documents_id=%1 "
            "UNION SELECT id FROM docpaths_documents WHERE documents_id=%1 "
            "UNION SELECT id FROM declar_documents WHERE documents_id=%1")
      .arg(id);
  if(!qry.exec(qryStr)){
    setError(tr("Ошибка получения информации об использовании документа: %1 "
                "QUERY: %2").arg(qry.lastError().text()).arg(qryStr));
    return false;
  }
  qry.next();
  if(qry.size()<1){
    qry.clear();
    LogDebug()<<"Deleting from documents, id ="<<id;
    qryStr=tr("DELETE FROM documents WHERE id=%1").arg(id);
    if(!qry.exec(qryStr)){
      setError(tr("Ошибка удаления документа: %1 QUERY: %2")
               .arg(qry.lastError().text()).arg(qryStr));
      return false;
    }
  }
  return true;
}
