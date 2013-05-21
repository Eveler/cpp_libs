#include "direction.h"

#include "direction_p.h"


Direction::~Direction()
{
  delete p;
  p = NULL;
}

void Direction::setName( const QString &name )
{
  p->m__Name = name;
  emit nameChanged();
}

const QString & Direction::name() const
{
  return p->m__Name;
}

bool Direction::addChildDirection( Direction *childDirection )
{
  if ( p->m__ChildDirections.contains( childDirection ) || p->exists( this ) ) return false;

  p->m__ChildDirections << childDirection;
  childDirection->p->setParentDirection( this );
  emit childDirectionAdded( childDirection );

  return true;
}

void Direction::removeChildDirection( Direction *childDirection )
{
  p->m__ChildDirections.removeOne( childDirection );
  childDirection->p->setParentDirection( NULL );
  emit childDirectionRemoved( childDirection );
}

Direction * Direction::parentDirection() const
{
  return p->m__ParentDirection;
}

const DirectionList & Direction::childDirections() const
{
  return p->m__ChildDirections;
}

Direction::Direction( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Direction_P( this );
}

