#include "group.h"

#include "group_p.h"


Group::~Group()
{
  delete p;
  p = NULL;
}

void Group::setName( const QString &name )
{
  p->m__Name = name;
  emit nameChanged();
}

const QString & Group::name() const
{
  return p->m__Name;
}

bool Group::addChildGroup( Group *childGroup )
{
  if ( p->m__ChildGroups.contains( childGroup ) || p->exists( this ) ) return false;

  p->m__ChildGroups << childGroup;
  childGroup->p->m__ParentGroups << this;
  emit childGroupAdded( childGroup );

  return true;
}

void Group::removeChildGroup( Group *childGroup )
{
  p->m__ChildGroups.removeOne( childGroup );
  childGroup->p->m__ParentGroups.removeOne( childGroup );
  emit childGroupRemoved( childGroup );
}

const GroupList & Group::parentGroups() const
{
  return p->m__ParentGroups;
}

const GroupList & Group::childGroups() const
{
  return p->m__ChildGroups;
}

Group::Group( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Group_P( this );
}

