#include "usersstorage.h"

#include "user.h"


UsersStorage *UsersStorage::m__Instance = NULL;

UsersStorage * UsersStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new UsersStorage;

  return m__Instance;
}

const UserList & UsersStorage::users() const
{
  return *((UserList *)(&objects()));
}

AbstractSimpleObjectList UsersStorage::findBySurname(
    const AbstractSimpleObjectList &objects, const QString &surname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->surname() == surname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByFirstname(
    const AbstractSimpleObjectList &objects, const QString &firstname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->firstname() == firstname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByLastname(
    const AbstractSimpleObjectList &objects, const QString &lastname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->lastname() == lastname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByPost(
    const AbstractSimpleObjectList &objects, Post *post ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->post() == post )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByDepartment(
    const AbstractSimpleObjectList &objects, Department *department ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->department() == department )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByActive(
    const AbstractSimpleObjectList &objects, bool active ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->active() == active )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByDismissed(
    const AbstractSimpleObjectList &objects, bool dismissed ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->dismissed() == dismissed )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByOffice(
    const AbstractSimpleObjectList &objects, Office *office ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    User *user = qobject_cast<User *>( object );
    if ( user->office() == office )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList UsersStorage::findByGroup(
    const AbstractSimpleObjectList &objects, Group *group ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

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

