#include "docpathsdocuments.h"
#include "docpathsdocsloader.h"
#include "docpathsdocssaver.h"
#include "amslogger.h"

DocpathsDocuments::DocpathsDocuments(const QVariant docpathsId,QSqlDatabase db,
                                     QObject *parent) :
  AbstractDocumentsList(docpathsId,db,parent),
  sortedModel(new QSortFilterProxyModel(this))
{
}

DocpathsDocuments::~DocpathsDocuments(){
//  LogDebug()<<"~DocpathsDocuments() BEGIN";
//  sortedModel->deleteLater();
  delete sortedModel;
//  LogDebug()<<"~DocpathsDocuments() END";
}

QSortFilterProxyModel *DocpathsDocuments::model(){
  if(!doclistModel){
    load(DB);
  }
  return sortedModel;
}

DocumentsModel *DocpathsDocuments::documents(){
  if(!doclistModel){
    load(DB);
  }
  return doclistModel;
}

void DocpathsDocuments::load(QSqlDatabase db){
  if(!loader){
    setLoader(new DocpathsDocsLoader(db,this));
    connect(loader,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
    ownLoader=true;
  }
  doclistModel=loader->load(ID);
  sortedModel->setSourceModel(doclistModel);
  sortedModel->sort(doclistModel->findColumn("created"),Qt::DescendingOrder);
}

bool DocpathsDocuments::saveDocuments(QSqlDatabase db, QString declar){
  LogDebug()<<"Saving DocpathsDocuments:"<<doclistModel->newDocuments().count()<<"docs";
  if(!saver){
    setSaver(new DocpathsDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocuments(doclistModel,declar);
}

bool DocpathsDocuments::saveDocList(QSqlDatabase db, QDateTime saveTime,
                                    bool initial){
  if(!saver){
    setSaver(new DocpathsDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocList(doclistModel,saveTime,initial);
}

bool DocpathsDocuments::saveDeleteDocuments(QSqlDatabase db){
  if(!saver){
    setSaver(new DocpathsDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDeleteDocuments(doclistModel);
}

void DocpathsDocuments::modelDestroyed(){
  doclistModel=NULL;
}
