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

User * UsersStorage::addUser( QVariant id )
{
  QList<User *> objs = findById( users(), id );
  if ( !objs.isEmpty() ) return objs.first();
  else
  {
    User *user = new User( id, this );
    connect( user, SIGNAL(destroyed(QObject*)), SLOT(userDestroyed(QObject*)) );
    m__Users << user;
    return user;
  }
}

const QList<User *> & UsersStorage::users() const
{
  return m__Users;
}

QList<User *> UsersStorage::findById( QList<User *> objs, QVariant value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->id() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByName( QList<User *> objs, StructName value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->name().surname == value.surname &&
         user->name().firstname == value.firstname &&
         user->name().lastname == value.lastname )
      result << user;

  return result;
}

QList<User *> UsersStorage::findByPost( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->post() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByDepartment( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->department() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByActive( QList<User *> objs, bool value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->active() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByDismissed( QList<User *> objs, bool value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->dismissed() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByOffice( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->office() == value ) result << user;

  return result;
}

UsersStorage::UsersStorage(QObject *parent) :
    QObject(parent)
{
}

UsersStorage::~UsersStorage()
{
}

void UsersStorage::userDestroyed( QObject *obj )
{
  User *user = (User *)obj;
  m__Users.removeOne( user );
}
