#ifndef USERSSTORAGE_H
#define USERSSTORAGE_H

#include <QObject>

#include "abstractsimplestorage.h"


class Post;
class Department;
class Office;
class Group;

class EXPORT UsersStorage : public AbstractSimpleStorage
{
    Q_OBJECT


public:
  static UsersStorage * instance();

  QList<AbstractSimpleObject *> findBySurname(
      const QList<AbstractSimpleObject *> &objects, const QString &surname ) const;
  QList<AbstractSimpleObject *> findByFirstname(
      const QList<AbstractSimpleObject *> &objects, const QString &firstname ) const;
  QList<AbstractSimpleObject *> findByLastname(
      const QList<AbstractSimpleObject *> &objects, const QString &lastname ) const;
  QList<AbstractSimpleObject *> findByPost(
      const QList<AbstractSimpleObject *> &objects, Post *post ) const;
  QList<AbstractSimpleObject *> findByDepartment(
      const QList<AbstractSimpleObject *> &objects, Department *department ) const;
  QList<AbstractSimpleObject *> findByActive(
      const QList<AbstractSimpleObject *> &objects, bool active ) const;
  QList<AbstractSimpleObject *> findByDismissed(
      const QList<AbstractSimpleObject *> &objects, bool dismissed ) const;
  QList<AbstractSimpleObject *> findByOffice(
      const QList<AbstractSimpleObject *> &objects, Office *office ) const;
  QList<AbstractSimpleObject *> findByGroup(
      const QList<AbstractSimpleObject *> &objects, Group *group ) const;


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static UsersStorage *m__Instance;

  explicit UsersStorage(QObject *parent = 0);
};

#endif // USERSSTORAGE_H
