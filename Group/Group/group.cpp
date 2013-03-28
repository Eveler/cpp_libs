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

Group::Group( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Group_P( this );
}

