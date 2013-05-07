#include "groupsstorage.h"

#include "group.h"


GroupsStorage *GroupsStorage::m__Instance = NULL;

GroupsStorage * GroupsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new GroupsStorage;

  return m__Instance;
}

const GroupList & GroupsStorage::groups() const
{
  return *((GroupList *)(&objects()));
}

AbstractSimpleObjectList GroupsStorage::findByName(
    const AbstractSimpleObjectList &objects, QString name )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Group *group = qobject_cast<Group *>( object );
    if ( group->name() == name )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList GroupsStorage::findByParent(
    const AbstractSimpleObjectList &objects, Group *parentGroup )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Group *group = qobject_cast<Group *>( object );
    if ( group->parentGroups().contains( parentGroup ) )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList GroupsStorage::findByChild(
    const AbstractSimpleObjectList &objects, Group *childGroup )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Group *group = qobject_cast<Group *>( object );
    if ( group->childGroups().contains( childGroup ) )
      result << object;
  }

  return result;
}

AbstractSimpleObject * GroupsStorage::createObject( QVariant id )
{
  return new Group( id, this );
}

GroupsStorage::GroupsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
