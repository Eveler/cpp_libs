#ifndef USERSSTORAGE_H
#define USERSSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/user_export_lib.h"


class Post;
class Department;
class Office;
class Group;
class User;

typedef QList<User *> UserList;

class EXPORT_USER UsersStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static UsersStorage * instance();

  const UserList & users() const;

  AbstractSimpleObjectList findBySurname(
      const AbstractSimpleObjectList &objects, const QString &surname ) const;
  AbstractSimpleObjectList findByFirstname(
      const AbstractSimpleObjectList &objects, const QString &firstname ) const;
  AbstractSimpleObjectList findByLastname(
      const AbstractSimpleObjectList &objects, const QString &lastname ) const;
  AbstractSimpleObjectList findByPost(
      const AbstractSimpleObjectList &objects, Post *post ) const;
  AbstractSimpleObjectList findByDepartment(
      const AbstractSimpleObjectList &objects, Department *department ) const;
  AbstractSimpleObjectList findByActive(
      const AbstractSimpleObjectList &objects, bool active ) const;
  AbstractSimpleObjectList findByDismissed(
      const AbstractSimpleObjectList &objects, bool dismissed ) const;
  AbstractSimpleObjectList findByOffice(
      const AbstractSimpleObjectList &objects, Office *office ) const;
  AbstractSimpleObjectList findByGroup(
      const AbstractSimpleObjectList &objects, Group *group ) const;


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static UsersStorage *m__Instance;

  explicit UsersStorage(QObject *parent = 0);
};

#endif // USERSSTORAGE_H
