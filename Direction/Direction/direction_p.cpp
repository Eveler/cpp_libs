#include "direction_p.h"

#include "department.h"


Direction_P::Direction_P( Direction *parent ) :
  QObject(parent)
{
  m__Name = QString();
  m__ParentDirection = NULL;
  m__ChildDirections = DirectionList();
  m__Department = NULL;
}

Direction_P::~Direction_P()
{
  if ( m__ParentDirection != NULL )
    disconnect( m__ParentDirection, SIGNAL(destroyed()), this, SLOT(parentDirectionDestroyed()) );
  m__ParentDirection = NULL;

  if ( m__Department != NULL )
    disconnect( m__Department, SIGNAL(destroyed()), this, SLOT(departmentDestroyed()) );
  m__Department = NULL;
}

Direction * Direction_P::p_dptr() const
{
  return qobject_cast<Direction *>( parent() );
}

bool Direction_P::exists( Direction *search ) const
{
  foreach ( Direction *direction, p_dptr()->childDirections() )
    if ( direction == search ) return true;
    else if ( direction->p->exists( search ) ) return true;

  return false;
}

void Direction_P::setParentDirection( Direction *parentDirection )
{
  if ( m__ParentDirection != NULL )
    disconnect( m__ParentDirection, SIGNAL(destroyed()), this, SLOT(parentDirectionDestroyed()) );

  if ( parentDirection != NULL ) setDepartment( NULL );

  m__ParentDirection = parentDirection;
  connect( m__ParentDirection, SIGNAL(destroyed()), SLOT(parentDirectionDestroyed()) );
}


void Direction_P::setDepartment( Department *department )
{
  if ( m__Department != NULL )
    disconnect( m__Department, SIGNAL(destroyed()), this, SLOT(departmentDestroyed()) );

  if ( department != NULL ) setParentDirection( NULL );

  m__Department = department;
  connect( m__Department, SIGNAL(destroyed()), SLOT(departmentDestroyed()) );
}

void Direction_P::parentDirectionDestroyed()
{
  m__ParentDirection = NULL;
}

void Direction_P::childDirectionDestroyed( QObject *object )
{
  m__ChildDirections.removeOne( ((Direction *)object) );
}

void Direction_P::departmentDestroyed()
{
  m__Department = NULL;
}

