#ifndef MDCLLOCK_H
#define MDCLLOCK_H

#include "export/mdcllock_global.h"
#include <QObject>
#include <QJsonDocument>
#include <QUrl>

class LockInfo{
public:
  int table_id;
  QString table_name;
  QString user;
  bool operator ==(const LockInfo& l){
    return table_id == l.table_id && table_name == l.table_name
        && user == l.user;
  }
};

class HttpClient;
class CheckConnection;
class MDCLLOCKSHARED_EXPORT MDclLock: public QObject
{
  Q_OBJECT
public:
  static MDclLock *instance();
  static bool lock(const int table_id, const QString &table_name,
                   const QString &user_name, const int priority=0,
                   const bool check_is_unlock_need=false);
  static void unlock(const int table_id, const QString &table_name, const QString &user);
  static QString locked_by(const int table_id, const QString &table_name);
  static MDclLock *is_unlock_need(const int table_id,
                                  const QString &table_name,
                                  const int priority=0);

  static void setLogin(const QString &login,
                       const QString &pass);
  static void setUrl(const QUrl &url);

  static QString &errorString(){return errStr;}
  static QString &message(){return msg;}

  ~MDclLock();

signals:
  void notification(QJsonDocument msg);
  void unlockRequired();
  void unlockRequired(int table_id, QString table_name, QString user_name);
  void unlockRequired(QString user_name);
  void error(QString str);

public slots:
  static void release();

private slots:
  void releaseClient();
  void unlockRequested();
  void errorRecieved(QString errStr);

private:
  MDclLock(QObject *parent=0);

  void initClient(const QUrl &url, const QString &login, const QString &pass);
  void registerOnServer();
  static bool checkSelf();
  static void set_error(const QString &str, const QString file, const int line);

  static MDclLock *self;
  static HttpClient *client;
  CheckConnection *cc;
  static QString errStr;
  static QString msg;

  QList< LockInfo > locks;
  QString m_login;
  QString m_pass;
  QUrl m_url;
};

#endif // MDCLLOCK_H
