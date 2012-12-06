#ifndef NOTIFICATIONSSTORAGE_H
#define NOTIFICATIONSSTORAGE_H

#include "storageitemmodel.h"
#include "notification.h"

typedef struct
{
  QString Id;
  QString Created;
  QString CreatorId;
} StructNotificationCols;

class NotificationsStorage : public QObject
{
  Q_OBJECT
public:
  explicit NotificationsStorage(QObject *parent = 0);
  ~NotificationsStorage();

  bool setStorage( StorageItemModel *stor, StructNotificationCols cols );
  StorageItemModel * storage() const;

  const QList<Notification *> & objects() const;

  QList<Notification *> findById( QList<Notification *> objs, QVariant id ) const;
  QList<Notification *> findByCreated(QList<Notification *> objs, QDateTime created ) const;
  QList<Notification *> findByCreator( QList<Notification *> objs, User *user ) const;

signals:

public slots:

protected:
  StructNotificationCols m__Cols;

private:
  StorageItemModel *m__Storage;

  QList<Notification *> m__Objects;

  void reset();
  void setObjectData( Notification *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *record, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // NOTIFICATIONSSTORAGE_H
