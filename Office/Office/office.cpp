#include "office.h"

#include "office_p.h"


Office::~Office()
{
  delete p;
  p = NULL;
}

void Office::setName( const QString &name )
{
  p->m__Name = name;
  emit nameChanged();
}

const QString & Office::name() const
{
  return p->m__Name;
}

Office::Office( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Office_P( this );
}

