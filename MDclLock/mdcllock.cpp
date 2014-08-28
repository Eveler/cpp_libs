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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
#endif
  if(!self) self = new MDclLock();
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"END";
#endif
  return self;
}

bool MDclLock::lock(const int table_id, const QString &table_name,
                    const QString &user_name, const int priority,
                    const bool check_is_unlock_need)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3, %4, %5 BEGIN")
              .arg(table_id).arg(table_name).arg(user_name).arg(priority)
              .arg(check_is_unlock_need);
#endif
  if(!checkSelf()) return true;
  if(self->recur_level>1){
    LogDebug()<<Q_FUNC_INFO<<"END";
    return true;
  }

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
    if(response.errorMessage().contains(tr("Must register first"))){
      delete self->client;
      self->client = NULL;
      self->recur_level++;
      bool res =
          lock(table_id, table_name, user_name, priority, check_is_unlock_need);
      self->recur_level--;
#ifdef MDCLLOCK_DEBUG
      LogDebug()<<Q_FUNC_INFO<<"END";
#endif
      return res;
    }
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

#ifdef MDCLLOCK_DEBUG
    LogDebug()<<Q_FUNC_INFO<<"END";
#endif
    return res;
  }
}

void MDclLock::unlock(const int table_id, const QString &table_name,
                      const int priority)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(table_id).arg(table_name).arg(priority);
#endif
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
#ifdef MDCLLOCK_DEBUG
    LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
    return;
  }else{
    LockInfo l;
    l.table_id = table_id;
    l.table_name = table_name;
    l.priority = priority;
    int i = self->locks.indexOf(l);
    if(i>-1) self->locks.removeAt(i);
  }
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

QString MDclLock::locked_by(const int table_id, const QString &table_name)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2 BEGIN")
              .arg(table_id).arg(table_name);
#endif
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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

MDclLock *MDclLock::is_unlock_need(const int table_id,
                              const QString &table_name, const int priority)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(table_id).arg(table_name).arg(priority);
#endif
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

#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
  return self;
}

void MDclLock::setLogin(const QString &login,
                        const QString &pass)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2 BEGIN")
              .arg(login).arg(pass);
#endif
  if(!self) instance();

  self->m_login = login;
  self->m_pass = pass;
  if(!self->m_url.isValid()){
#ifdef MDCLLOCK_DEBUG
    LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
    return;
  }

  self->initClient(self->m_url, self->m_login, self->m_pass);
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

void MDclLock::setUrl(const QUrl &url)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1 BEGIN")
              .arg(url.toString());
#endif
  if(!self) instance();

  if(url.isValid()) self->m_url = url;
  else{
    setError(tr("Ошибочный адресс"));
    return;
  }
  if(self->m_login.isEmpty()){
#ifdef MDCLLOCK_DEBUG
    LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
    return;
  }

  self->initClient(self->m_url, self->m_login, self->m_pass);
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

MDclLock::~MDclLock()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
#endif
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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"END";
#endif
}

void MDclLock::release()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
#endif
  if(self){
    delete self;
    self = NULL;
  }
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"END";
#endif
}

void MDclLock::releaseClient()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"BEGIN";
#endif
  if(client){
    delete client;
    client = NULL;
  }
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<"END";
#endif
}

void MDclLock::unlockRequested()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
#endif
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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

void MDclLock::errorRecieved(QString errStr)
{
  setError(errStr);
}

MDclLock::MDclLock(QObject *parent): QObject(parent),cc(NULL),recur_level(0)
{
  connect(qApp, SIGNAL(aboutToQuit()), SLOT(release()));
}

void MDclLock::initClient(const QUrl &url, const QString &login,
                          const QString &pass)
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("Params: %1, %2, %3 BEGIN")
              .arg(url.toString()).arg(login).arg(pass);
#endif
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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

void MDclLock::registerOnServer()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
#endif
  QJsonRpcMessage response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("register"));
  if(response.type() == QJsonRpcMessage::Error){
    delete client;
    client = NULL;
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
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
}

bool MDclLock::checkSelf()
{
#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("BEGIN");
#endif
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

#ifdef MDCLLOCK_DEBUG
  LogDebug()<<Q_FUNC_INFO<<tr("END");
#endif
  return self->client != NULL;
}

void MDclLock::set_error(const QString &str, const QString file, const int line)
{
  LogWarning()<<file<<tr("(")<<line<<tr("): ")<<str;
  errStr = str;
  if(self) emit self->error(str);
}
