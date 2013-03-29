#include "group_p.h"


Group_P::Group_P( Group *parent ) :
  QObject(parent)
{
  m__Name = QString();
  m__ParentGroups = GroupList();
  m__ChildGroups = GroupList();
}

Group * Group_P::p_dptr() const
{
  return qobject_cast<Group *>( parent() );
}

bool Group_P::exists( Group *search ) const
{
  foreach ( Group *group, p_dptr()->childGroups() )
    if ( group == search ) return true;
    else if ( group->p->exists( search ) ) return true;

  return false;
}

void Group_P::parentGroupDestroyed( QObject *object )
{
  m__ParentGroups.removeOne( ((Group *)object) );
}

void Group_P::childGroupDestroyed( QObject *object )
{
  m__ChildGroups.removeOne( ((Group *)object) );
}

