#include "mdcllock.h"
#include "httpclient.h"
#include "amslogger.h"
#include "checkconnection.h"
#include <QJsonDocument>
#include <QUuid>

#define setError(str) set_error(str, __FILE__, __LINE__)

MDclLock *MDclLock::self = NULL;
HttpClient *MDclLock::client = NULL;
QString MDclLock::errStr = QString();
QString MDclLock::msg = QString();


MDclLock *MDclLock::instance()
{
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
  if(!self) self = new MDclLock();
  LogDebug()<<Q_FUNC_INFO<<"END";
  return self;
}

bool MDclLock::lock(const int table_id, const QString &table_name,
                    const QString &user_name, const int priority,
                    const bool check_is_unlock_need)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3, %4, %5 BEGIN")
              .arg(table_id).arg(table_name).arg(user_name).arg(priority)
              .arg(check_is_unlock_need);
  return true;
  if(!checkSelf()) return true;

  LockInfo l;
  l.table_id = table_id;
  l.table_name = table_name;
  l.priority = priority;
  if(self->locks.indexOf(l)>-1)
    LogWarning()<<tr("Lock <%1(%2) pririty = %3> already set")
                  .arg(table_name).arg(table_id).arg(priority);

  QJsonArray params;
  params.append(table_id);
  params.append(table_name);
  params.append(user_name);
  params.append(priority);
  QJsonRpcMessage response = self->client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("lock", params));

  if(response.type() == QJsonRpcMessage::Error){
    setError(tr("errorMessage = %1; errorData = %2; code = %3")
             .arg(response.errorMessage())
             .arg(response.errorData().toString())
             .arg(response.errorCode()));
    return true;
  }else{
    bool res = response.result().toBool();

    if(res){
      LockInfo l;
      l.table_id = table_id;
      l.table_name = table_name;
      l.priority = priority;
      if(self->locks.indexOf(l)<0) self->locks << l;
      if(check_is_unlock_need) is_unlock_need(table_id, table_name, priority);
    }else{
      msg = locked_by(table_id, table_name);
    }

    return res;
  }
  LogDebug()<<Q_FUNC_INFO<<"END";
}

void MDclLock::unlock(const int table_id, const QString &table_name,
                      const int priority)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(table_id).arg(table_name).arg(priority);
  return;
  if(!checkSelf()) return;

  QJsonArray params;
  params.append(table_id);
  params.append(table_name);
  params.append(priority);
  QJsonRpcMessage response = self->client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("unlock", params));

  if(response.type() == QJsonRpcMessage::Error){
    setError(tr("errorMessage = %1; errorData = %2; code = %3")
             .arg(response.errorMessage())
             .arg(response.errorData().toString())
             .arg(response.errorCode()));
    LogDebug()<<Q_FUNC_INFO<<tr("END");
    return;
  }else{
    LockInfo l;
    l.table_id = table_id;
    l.table_name = table_name;
    l.priority = priority;
    int i = self->locks.indexOf(l);
    if(i>-1) self->locks.removeAt(i);
  }
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

QString MDclLock::locked_by(const int table_id, const QString &table_name)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2 BEGIN")
              .arg(table_id).arg(table_name);
  if(!checkSelf()) return QString();

  QJsonArray params;
  params.append(table_id);
  params.append(table_name);
  QJsonRpcMessage response = self->client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("locked_by", params));

  if(response.type() == QJsonRpcMessage::Error){
    setError(tr("errorMessage = %1; errorData = %2; code = %3")
             .arg(response.errorMessage())
             .arg(response.errorData().toString())
             .arg(response.errorCode()));
    return QString();
  }else{
    return response.result().toString();
  }
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

MDclLock *MDclLock::is_unlock_need(const int table_id,
                              const QString &table_name, const int priority)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(table_id).arg(table_name).arg(priority);
  /// воспользуемся long poling для получения сообщения о необходимости
  /// разблокировать запись
  /// приэтом нужно соединить сигнал \fn unlockRequired() с методом снятия
  /// блокировки
  if(!checkSelf()) return NULL;

  QJsonArray params;
  params.append(table_id);
  params.append(table_name);
  params.append(priority);
  QJsonRpcServiceReply *reply = self->client->sendMessage(
        QJsonRpcMessage::createRequest("is_unlock_need", params));
  connect(reply, SIGNAL(finished()), self, SLOT(unlockRequested()));

  LogDebug()<<Q_FUNC_INFO<<tr("END");
  return self;
}

void MDclLock::setLogin(const QString &login,
                        const QString &pass)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2 BEGIN")
              .arg(login).arg(pass);
  if(!self) instance();

  self->m_login = login;
  self->m_pass = pass;
  if(!self->m_url.isValid()){
    LogDebug()<<Q_FUNC_INFO<<tr("END");
    return;
  }

  self->initClient(self->m_url, self->m_login, self->m_pass);
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

void MDclLock::setUrl(const QUrl &url)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1 BEGIN")
              .arg(url.toString());
  if(!self) instance();

  if(url.isValid()) self->m_url = url;
  else{
    setError(tr("Ошибочный адресс"));
    return;
  }
  if(self->m_login.isEmpty()){
    LogDebug()<<Q_FUNC_INFO<<tr("END");
    return;
  }

  self->initClient(self->m_url, self->m_login, self->m_pass);
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

MDclLock::~MDclLock()
{
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
  errStr.clear();
  msg.clear();

  // отчистим все блокировки
  while(!locks.isEmpty()){
    LockInfo l = locks.first();
    LogWarning()<<"Unlock"<<l.table_name<<"("<<l.table_id<<")";
    unlock(l.table_id, l.table_name, l.priority);
  }

  if(cc){
    delete cc;
  }

  releaseClient();
  self = NULL;
  LogDebug()<<Q_FUNC_INFO<<"END";
}

void MDclLock::release()
{
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
  if(self){
    delete self;
    self = NULL;
  }
  LogDebug()<<Q_FUNC_INFO<<"END";
}

void MDclLock::releaseClient()
{
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
  if(client){
    delete client;
    client = NULL;
  }
  LogDebug()<<Q_FUNC_INFO<<"END";
}

void MDclLock::unlockRequested()
{
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
  QJsonRpcServiceReply *reply = qobject_cast<QJsonRpcServiceReply*>(sender());
  if(!reply) return;

  QJsonDocument doc(reply->response().toObject());
  emit notification(doc);
  if(reply->response().result().isObject()){
    QJsonObject obj = reply->response().result().toObject();
    emit unlockRequired();
    emit unlockRequired(obj.value("table_id").toInt(),
                        obj.value("table_name").toString(),
                        obj.value("user").toString());
    emit unlockRequired(obj.value("user").toString());
  }else if(reply->response().result().toBool()){
    emit unlockRequired();
    emit unlockRequired(tr("не определён"));
  }
  reply->deleteLater();
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

void MDclLock::errorRecieved(QString errStr)
{
  setError(errStr);
}

MDclLock::MDclLock(QObject *parent): QObject(parent),cc(NULL)
{
  connect(qApp, SIGNAL(aboutToQuit()), SLOT(release()));
}

void MDclLock::initClient(const QUrl &url, const QString &login,
                          const QString &pass)
{
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(url.toString()).arg(login).arg(pass);
  if(!self->client){
    self->client = new HttpClient(url.toString(), login, pass, self);
    // register on server now
    self->registerOnServer();
    connect(qApp, SIGNAL(aboutToQuit()), self, SLOT(releaseClient()));
  }else{
    self->client->setEndPoint(url);
    self->client->setUsername(login);
    self->client->setPassword(pass);
  }
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

void MDclLock::registerOnServer()
{
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
  QJsonRpcMessage response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("register"));
  if(response.type() == QJsonRpcMessage::Error){
    setError(tr("errorMessage = %1; errorData = %2; code = %3")
             .arg(response.errorMessage())
             .arg(response.errorData().toString())
             .arg(response.errorCode()));
  }else{
    QString res = response.result().toString();

    if(!QUuid(res).isNull()){
      if(cc) delete cc;
      QUrl url = client->endPoint();
      cc = new CheckConnection(res, url.host(), url.port(9166)+1, this);
      connect(cc,SIGNAL(error(QString)),SLOT(errorRecieved(QString)));
      connect(cc,SIGNAL(disconnected()),SIGNAL(unlockRequired()));
      connect(cc, SIGNAL(disconnected()), SLOT(releaseClient()));
    }
  }
  LogDebug()<<Q_FUNC_INFO<<tr("END");
}

bool MDclLock::checkSelf()
{
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
  if(!self){
    instance();
    LogWarning()<<"Need to setLogin and setUrl";
    return false;
  }

  if(!self->client){
    if(self->m_login.isEmpty() && !self->m_url.isValid()){
      LogWarning()<<"Need to setLogin and setUrl";
      return false;
    }else self->initClient(self->m_url, self->m_login, self->m_pass);
  }

  LogDebug()<<Q_FUNC_INFO<<tr("END");
  return true;
}

void MDclLock::set_error(const QString &str, const QString file, const int line)
{
  LogWarning()<<file<<tr("(")<<line<<tr("): ")<<str;
  errStr = str;
  if(self) emit self->error(str);
}
