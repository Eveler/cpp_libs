#include "mdcllock.h"
#include "httpclient.h"
#include "amslogger.h"
#include <QJsonDocument>


MDclLock *MDclLock::self = NULL;

MDclLock *MDclLock::instance(const QUrl &url)
{
  if(!self) self = new MDclLock(url);
  return self;
}

bool MDclLock::lock(const QVariant &table_id, const QString &table_name,
                    const QString &user_name, const int priority)
{
  if(!self){
    instance();
    LogWarning()<<"Need to setLogin";
    return true;
  }

  if(!self->client){
    LogWarning()<<"Need to setLogin";
    return true;
  }

  QJsonArray params;
  params.append(table_id.toJsonValue());
  params.append(table_name);
  params.append(user_name);
  params.append(priority);
  QJsonRpcMessage response = self->client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("lock", params));

  if(response.type() == QJsonRpcMessage::Error){
    LogCritical()<<response.errorData().toString();
    return true;
  }else{
    QJsonDocument doc(response.toObject());
    LogDebug()<<doc.toJson();
    LogDebug()<<doc.toVariant();
    return doc.toVariant().toBool();
  }

  return true;
}

MDclLock::~MDclLock()
{
  if(client) delete client;
  self = NULL;
}

MDclLock::MDclLock(QObject *parent): QObject(parent)
{
}

MDclLock::MDclLock(const QUrl &url, QObject *parent):
  QObject(parent)
{
  client = new HttpClient(url.toString(), this);
}
