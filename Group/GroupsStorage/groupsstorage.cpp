#include "groupsstorage.h"

#include "group.h"


GroupsStorage *GroupsStorage::m__Instance = NULL;

GroupsStorage * GroupsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new GroupsStorage;

  return m__Instance;
}

QList<AbstractSimpleObject *> GroupsStorage::findByName(
    QList<AbstractSimpleObject *> objects, QString name )
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Group *group = qobject_cast<Group *>( object );
    if ( group->name() == name )
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
