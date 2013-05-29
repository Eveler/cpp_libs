#include "clientdocuments.h"
#include "clientdocsloader.h"
#include "clientdocssaver.h"
#include "amslogger.h"

ClientDocuments::ClientDocuments(const QVariant clientId,QSqlDatabase db,
                                 QObject *parent) :
  AbstractDocumentsList(clientId,db,parent),
  sortedModel(new QSortFilterProxyModel(this))
{
}

ClientDocuments::~ClientDocuments(){
  LogDebug()<<"~ClientDocuments() BEGIN";
  sortedModel->deleteLater();
  LogDebug()<<"~ClientDocuments() END";
}

QSortFilterProxyModel *ClientDocuments::model(){
  if(!doclistModel){
    load(DB);
  }
  return sortedModel/*doclistModel*/;
}

DocumentsModel *ClientDocuments::documents(){
  if(!doclistModel){
    load(DB);
  }
  return doclistModel;
}

void ClientDocuments::load(QSqlDatabase db){
  if(!loader){
    setLoader(new ClientDocsLoader(db,this));
    connect(loader,SIGNAL(modelDestroyed()),SLOT(modelDestroyed()));
    ownLoader=true;
  }
  doclistModel=loader->load(ID);
  sortedModel->setSourceModel(doclistModel);
  sortedModel->sort(doclistModel->findColumn("created"),Qt::DescendingOrder);
}

bool ClientDocuments::saveDocuments(QSqlDatabase db, QString declar){
  LogDebug()<<"Saving ClientDocuments:"<<doclistModel->newDocuments().count()<<"docs";
  if(!saver){
    setSaver(new ClientDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocuments(doclistModel,declar);
}

bool ClientDocuments::saveDocList(QSqlDatabase db, QDateTime saveTime,
                                  bool initial){
  if(!saver){
    setSaver(new ClientDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDocList(doclistModel,saveTime,initial);
}

void ClientDocuments::modelDestroyed(){
  doclistModel=NULL;
}
