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

Post::Post( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Post_P( this );
}

