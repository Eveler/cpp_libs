#ifndef USERSSTORAGE_H
#define USERSSTORAGE_H

#include <QObject>

#include "user.h"


class EXPORT UsersStorage : public QObject
{
    Q_OBJECT


public:
  static UsersStorage * instance();

  User * addUser( QVariant id );

  const QList<User *> & users() const;

  QList<User *> findById( QList<User *> objs, QVariant value ) const;
  QList<User *> findByName( QList<User *> objs, StructName value ) const;
  QList<User *> findByPost( QList<User *> objs, AbstractSimpleObject *value ) const;
  QList<User *> findByDepartment( QList<User *> objs, AbstractSimpleObject *value ) const;
  QList<User *> findByActive( QList<User *> objs, bool value ) const;
  QList<User *> findByDismissed( QList<User *> objs, bool value ) const;
  QList<User *> findByOffice( QList<User *> objs, AbstractSimpleObject *value ) const;


signals:


public slots:


private:
  static UsersStorage *m__Instance;

  QList<User *> m__Users;

  explicit UsersStorage(QObject *parent = 0);
  ~UsersStorage();


private slots:
  void userDestroyed( QObject *obj );
};

#endif // USERSSTORAGE_H
