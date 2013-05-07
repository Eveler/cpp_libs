#include "directionsstorage.h"

#include "direction.h"


DirectionsStorage *DirectionsStorage::m__Instance = NULL;

DirectionsStorage * DirectionsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DirectionsStorage;

  return m__Instance;
}

const DirectionList & DirectionsStorage::Directions() const
{
  return *((DirectionList *)(&objects()));
}

AbstractSimpleObjectList DirectionsStorage::findByName(
    const AbstractSimpleObjectList &objects, QString name )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Direction *direction = qobject_cast<Direction *>( object );
    if ( direction->name() == name )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList DirectionsStorage::findByParent(
    const AbstractSimpleObjectList &objects, Direction *parentDirection )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Direction *direction = qobject_cast<Direction *>( object );
    if ( direction->parentDirection() == parentDirection )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList DirectionsStorage::findByChild(
    const AbstractSimpleObjectList &objects, Direction *childDirection )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Direction *direction = qobject_cast<Direction *>( object );
    if ( direction->childDirections().contains( childDirection ) )
      result << object;
  }

  return result;
}

AbstractSimpleObjectList DirectionsStorage::findByDepartment(
    const AbstractSimpleObjectList &objects, Department *department )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Direction *direction = qobject_cast<Direction *>( object );
    if ( direction->department() == department )
      result << object;
  }

  return result;
}

AbstractSimpleObject * DirectionsStorage::createObject( QVariant id )
{
  return new Direction( id, this );
}

DirectionsStorage::DirectionsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
