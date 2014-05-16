#ifndef MDCLLOCK_H
#define MDCLLOCK_H

#include "export/mdcllock_global.h"
#include <QObject>
#include <QJsonDocument>

class HttpClient;
class CheckConnection;
class MDCLLOCKSHARED_EXPORT MDclLock: public QObject
{
  Q_OBJECT
public:
  static MDclLock *instance() {if(!self) self = new MDclLock();return self;}
  static MDclLock *instance(const QUrl &url);
  static bool lock(const int table_id, const QString &table_name,
                   const QString &user_name, const int priority=0);
  static void unlock(const int table_id, const QString &table_name);
  static QString locked_by(const int table_id, const QString &table_name);
  static MDclLock *is_unlock_need(const int table_id,
                                  const QString &table_name,
                                  const int priority=0);

  static void setLogin(const QUrl &url, const QString &login,
                       const QString &pass);

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
  MDclLock(const QUrl &url, QObject *parent=0);

  void registerOnServer();
  static bool checkSelf();
  static void set_error(const QString &str, const QString file, const int line);

  static MDclLock *self;
  static HttpClient *client;
  CheckConnection *cc;
  static QString errStr;
  static QString msg;

  QList< QPair<int, QString> > locks;
};

#endif // MDCLLOCK_H
