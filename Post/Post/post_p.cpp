#include "post_p.h"

#include "post.h"


Post_P::Post_P( Post *parent ) :
  QObject(parent)
{
  m__Name = QString();
}

Post * Post_P::p_dptr() const
{
  return qobject_cast<Post *>( parent() );
}
