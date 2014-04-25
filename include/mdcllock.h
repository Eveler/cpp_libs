#ifndef MDCLLOCK_H
#define MDCLLOCK_H

#include "export/mdcllock_global.h"
#include <QObject>


class HttpClient;
class MDCLLOCKSHARED_EXPORT MDclLock: public QObject
{
  Q_OBJECT
public:
  static MDclLock *instance() {if(!self) self = new MDclLock();return self;}
  static MDclLock *instance(const QUrl &url);
  static bool lock(const QVariant &table_id, const QString &table_name,
                   const QString &user_name, const int priority=999);
  static void unlock(const QVariant &table_id, const QString &table_name);

  static void setLogin(const QString &login, const QString &pass);

  ~MDclLock();

signals:
  void notification(QString msg);
  void unlockRequired();

private:
  MDclLock(QObject *parent=0);
  MDclLock(const QUrl &url, QObject *parent=0);

  static MDclLock *self;
  HttpClient *client;
};

#endif // MDCLLOCK_H
