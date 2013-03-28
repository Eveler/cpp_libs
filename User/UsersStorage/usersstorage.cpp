#include "usersstorage.h"

#include "user.h"


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

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->surname() == surname )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByFirstname(
    const QList<AbstractSimpleObject *> &objects, const QString &firstname ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->firstname() == firstname )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByLastname(
    const QList<AbstractSimpleObject *> &objects, const QString &lastname ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->lastname() == lastname )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByPost(
    const QList<AbstractSimpleObject *> &objects, Post *post ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->post() == post )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByDepartment(
    const QList<AbstractSimpleObject *> &objects, Department *department ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->department() == department )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByActive(
    const QList<AbstractSimpleObject *> &objects, bool active ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->active() == active )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByDismissed(
    const QList<AbstractSimpleObject *> &objects, bool dismissed ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->dismissed() == dismissed )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByOffice(
    const QList<AbstractSimpleObject *> &objects, Office *office ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->office() == office )
      result << object;
  }

  return result;
}

QList<AbstractSimpleObject *> UsersStorage::findByGroup(
    const QList<AbstractSimpleObject *> &objects, Group *group ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->group() == group )
      result << object;
  }

  return result;
}

AbstractSimpleObject * UsersStorage::createObject( QVariant id )
{
  return new User( id, this );
}

UsersStorage::UsersStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

