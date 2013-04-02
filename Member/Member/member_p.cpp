#include "member_p.h"

#include "member.h"
#include "post.h"
#include "group.h"


Member_P::Member_P( Member *parent ) :
  QObject(parent)
{
  m__Surname = QString();
  m__Firstname = QString();
  m__Lastname = QString();
  m__Post = NULL;
  m__Active = false;
  m__Dismissed = false;
  m__Group = NULL;
}

Member_P::~Member_P()
{
  if ( m__Post != NULL )
    disconnect( m__Post, SIGNAL(destroyed()), this, SLOT(postDestroyed()) );
  m__Post = NULL;

  if ( m__Group != NULL )
    disconnect( m__Group, SIGNAL(destroyed()), this, SLOT(groupDestroyed()) );
  m__Group = NULL;
}

Member * Member_P::p_dptr() const
{
  return qobject_cast<Member *>( parent() );
}

void Member_P::setPost( Post *post )
{
  if ( m__Post != NULL )
    disconnect( m__Post, SIGNAL(destroyed()), this, SLOT(postDestroyed()) );

  m__Post = post;
  connect( m__Post, SIGNAL(destroyed()), SLOT(postDestroyed()) );
}

void Member_P::setGroup( Group *group )
{
  if ( m__Group != NULL )
    disconnect( m__Group, SIGNAL(destroyed()), this, SLOT(groupDestroyed()) );

  m__Group = group;
  connect( m__Group, SIGNAL(destroyed()), SLOT(groupDestroyed()) );
}

void Member_P::postDestroyed()
{
  m__Post = NULL;
}

void Member_P::groupDestroyed()
{
  m__Group = NULL;
}
