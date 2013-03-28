#include "department_p.h"

#include "department.h"


Department_P::Department_P( Department *parent ) :
  QObject(parent)
{
  m__Name = QString();
}

Department * Department_P::p_dptr() const
{
  return qobject_cast<Department *>( parent() );
}
