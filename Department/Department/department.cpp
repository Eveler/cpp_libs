#include "department.h"

#include "department_p.h"

#include <QVariant>


Department::~Department()
{
  delete p;
  p = NULL;
}

void Department::setName( const QString &name )
{
  p->m__Name = name;
  emit nameChanged();
}

const QString & Department::name() const
{
  return p->m__Name;
}

Department::Department( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Department_P( this );
}

