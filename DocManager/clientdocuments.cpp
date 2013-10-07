#include "clientdocuments.h"
#include "clientdocsloader.h"
#include "clientdocssaver.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

ClientDocuments::ClientDocuments(const QVariant clientId,QSqlDatabase db,
                                 QObject *parent) :
  AbstractDocumentsList(clientId,db,parent),
  sortedModel(new QSortFilterProxyModel(this))
{
}

ClientDocuments::~ClientDocuments(){
  LogDebug()<<"~ClientDocuments() BEGIN";
//  sortedModel->deleteLater();
  delete sortedModel;
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
  doclistModel->setObjectName(tr("ClientDocuments_model_%1").arg(ID.toString()));
  sortedModel->setSourceModel(doclistModel);
  sortedModel->sort(doclistModel->findColumn("created"),Qt::DescendingOrder);
}

bool ClientDocuments::load( MFCDocumentInfo *doc )
{
  if ( loader == NULL ) return false;

  return loader->load( doc );
}

bool ClientDocuments::saveDocuments(QSqlDatabase db, QString declar){
  LogDebug()<<"Saving ClientDocuments:"<<documents()->newDocuments().count()
           <<"docs";
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
  return saver->saveDocList(documents(),saveTime,initial);
}

bool ClientDocuments::saveDeleteDocuments(QSqlDatabase db){
  if(!saver){
    setSaver(new ClientDocsSaver(db,ID.toString(),this));
    ownSaver=true;
  }
  return saver->saveDeleteDocuments(documents());
}

void ClientDocuments::modelDestroyed(){
  doclistModel=NULL;
}
