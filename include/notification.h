#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

#include "user.h"

#include <QVariant>
#include <QDateTime>

class Notification : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QDateTime m__Created;
    User *m__Creator;
  } StructNotification;
  Q_OBJECT
public:
  explicit Notification(QObject *parent = 0);
  ~Notification();

  const QVariant & id() const;
  QDateTime created() const;
  User * creator() const;

signals:

public slots:
  void clear();

  void setId( QVariant value );
  void setCreated( QDateTime value );
  void setCreator( User *value );

private:
  StructNotification m__Value;
};

#endif // NOTIFICATION_H
