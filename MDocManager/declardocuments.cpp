#include "declardocuments.h"
#include "declardocsloader.h"
#include "declardocssaver.h"
#include "amslogger.h"

DeclarDocuments::DeclarDocuments(const QVariant declarId,QSqlDatabase db,
                                 QObject *parent) :
  AbstractDocumentsList(declarId,db,parent),
  sortedModel(new QSortFilterProxyModel(this))
{
}

DeclarDocuments::~DeclarDocuments(){
  LogDebug()<<"~DeclarDocuments() BEGIN";
  sortedModel->deleteLater();
  LogDebug()<<"~DeclarDocuments() END";
}

QSortFilterProxyModel *DeclarDocuments::model(){
  if(!doclistModel){
    load(DB);
  }
  return sortedModel;
}

DocumentsModel *DeclarDocuments::documents(){
  if(!doclistModel){
    load(DB);
  }
  return doclistModel;
}

void DeclarDocuments::load(QSqlDatabase db){
  if(!loader){
    setLoader(new DeclarDocsLoader(db,this));
    connect(loader,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
    ownLoader=true;
  }
  doclistModel=loader->load(ID);
  sortedModel->setSourceModel(doclistModel);
  sortedModel->sort(doclistModel->findColumn("created"),Qt::DescendingOrder);
}

bool DeclarDocuments::saveDocuments(QSqlDatabase db,QString declar){
  LogDebug()<<"Saving declarDocs:"<<doclistModel->newDocuments().count()<<"docs";
  if(!saver){
    setSaver(new DeclarDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocuments(doclistModel,declar);
}

bool DeclarDocuments::saveDocList(QSqlDatabase db, QDateTime saveTime,
                                  bool initial){
  if(!saver){
    setSaver(new DeclarDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocList(doclistModel,saveTime,initial);
}

void DeclarDocuments::modelDestroyed(){
  doclistModel=NULL;
}
