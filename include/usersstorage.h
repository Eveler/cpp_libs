#ifndef USERSSTORAGE_H
#define USERSSTORAGE_H

#include "storageitemmodel.h"
#include "user.h"

typedef struct
{
  QString Id;
  QString Surname;
  QString Firstname;
  QString Lastname;
  QString PostId;
  QString DepartmentId;
  QString Active;
  QString Dismissed;
  QString OfficeId;
} StructUserCols;

class UsersStorage : public QObject
{
    Q_OBJECT
public:
  static UsersStorage * instance();

  bool setStorage( StorageItemModel *stor, StructUserCols cols );
  StorageItemModel * storage() const;

  const QList<User *> & objects() const;

  QList<User *> findById( QVariant value, QList<User *> objs ) const;
  QList<User *> findByName( StructName value, QList<User *> objs ) const;
  QList<User *> findByPost( AbstractSimpleObject *value, QList<User *> objs ) const;
  QList<User *> findByDepartment( AbstractSimpleObject *value, QList<User *> objs ) const;
  QList<User *> findByActive( bool value, QList<User *> objs ) const;
  QList<User *> findByDismissed( bool value, QList<User *> objs ) const;
  QList<User *> findByOffice( AbstractSimpleObject *value, QList<User *> objs ) const;

signals:

public slots:

private:
  static UsersStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructUserCols m__Cols;

  QList<User *> m__Users;

  explicit UsersStorage(QObject *parent = 0);
  ~UsersStorage();

  void reset();
  void setObjectData( User *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // USERSSTORAGE_H
