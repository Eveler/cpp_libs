#include "usersstorage.h"

#include "postsstorage.h"
#include "departmentsstorage.h"
#include "officesstorage.h"

UsersStorage *UsersStorage::m__Instance = NULL;

UsersStorage * UsersStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new UsersStorage;

  return m__Instance;
}

QList<AbstractSimpleObject *> UsersStorage::findBySurname(
    const QList<AbstractSimpleObject *> &objects, const QString &surname ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
  {
    if ( user->name().surname == value.surname &&
         user->name().firstname == value.firstname &&
         user->name().lastname == value.lastname )
      result << user;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByPost(
    QList<AbstractSimpleObject *> objects, Post *post ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
    if ( user->post() == post ) result << user;

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByDepartment(
    QList<AbstractSimpleObject *> objects, Department *department ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
    if ( user->department() == department ) result << user;

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByActive(
    QList<AbstractSimpleObject *> objects, bool active ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
    if ( user->active() == active ) result << user;

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByDismissed(
    QList<AbstractSimpleObject *> objects, bool dismissed ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
    if ( user->dismissed() == dismissed ) result << user;

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByOffice(
    QList<AbstractSimpleObject *> objects, Office *office ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( User *user, objs )
    if ( user->office() == office ) result << user;

  return result;
}

AbstractSimpleObject * UsersStorage::createObject( QVariant id )
{
  return new User( id, this );
}

UsersStorage::UsersStorage(QObject *parent) :
    QObject(parent)
{
}

