#include "abstractsimpleobject.h"


AbstractSimpleObject::AbstractSimpleObject( QVariant id, QObject *parent ) :
  QObject(parent),
  m__Id(id)
{
}

const QVariant & AbstractSimpleObject::id() const
{
  return m__Id;
}

