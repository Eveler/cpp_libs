#include "post_p.h"

#include "post.h"
#include "direction.h"


Post_P::Post_P( Post *parent ) :
  QObject(parent)
{
  m__Name = QString();
}

Post_P::~Post_P()
{
  if ( m__Direction != NULL )
    disconnect( m__Direction, SIGNAL(destroyed()), this, SLOT(directionDestroyed()) );
  m__Direction = NULL;
}

Post * Post_P::p_dptr() const
{
  return qobject_cast<Post *>( parent() );
}

void Post_P::setDirection( Direction *direction )
{
  if ( m__Direction != NULL )
    disconnect( m__Direction, SIGNAL(destroyed()), this, SLOT(directionDestroyed()) );

  m__Direction = direction;
  connect( m__Direction, SIGNAL(destroyed()), SLOT(directionDestroyed()) );
}

void Post_P::directionDestroyed()
{
  m__Direction = NULL;
}
