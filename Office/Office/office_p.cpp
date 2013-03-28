#include "office_p.h"

#include "office.h"


Office_P::Office_P( Office *parent ) :
  QObject(parent)
{
  m__Name = QString();
}

Office * Office_P::p_dptr() const
{
  return qobject_cast<Office *>( parent() );
}
