#include "membersstorage.h"

#include "member.h"


MembersStorage *MembersStorage::m__Instance = NULL;

MembersStorage * MembersStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new MembersStorage;

  return m__Instance;
}

const MemberList & MembersStorage::members() const
{
  return *((MemberList *)(&objects()));
}

AbstractSimpleObjectList MembersStorage::findBySurname(
    const AbstractSimpleObjectList &objects, const QString &surname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->surname() == surname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByFirstname(
    const AbstractSimpleObjectList &objects, const QString &firstname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->firstname() == firstname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByLastname(
    const AbstractSimpleObjectList &objects, const QString &lastname ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->lastname() == lastname )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByPost(
    const AbstractSimpleObjectList &objects, Post *post ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->post() == post )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByActive(
    const AbstractSimpleObjectList &objects, bool active ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->active() == active )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByDismissed(
    const AbstractSimpleObjectList &objects, bool dismissed ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->dismissed() == dismissed )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList MembersStorage::findByGroup(
    const AbstractSimpleObjectList &objects, Group *group ) const
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();

  foreach ( AbstractSimpleObject *object, objects )
  {
    Member *member = qobject_cast<Member *>( object );
    if ( member->group() == group )
      result << object;
  }

  return result;
}

AbstractSimpleObject * MembersStorage::createObject( QVariant id )
{
  return new Member( id, this );
}

MembersStorage::MembersStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

