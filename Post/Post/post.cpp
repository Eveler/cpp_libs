#include "post.h"

#include "post_p.h"


Post::~Post()
{
  delete p;
  p = NULL;
}

void Post::setName( const QString &name )
{
  p->m__Name = name;
  emit nameChanged();
}

const QString & Post::name() const
{
  return p->m__Name;
}

void Post::setDirection( Direction *direction )
{
  p->setDirection( direction );
  emit directionChanged();
}

Direction * Post::direction() const
{
  return p->m__Direction;
}

Post::Post( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Post_P( this );
}

