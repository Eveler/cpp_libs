#include "group_p.h"

#include "group.h"


Group_P::Group_P( Group *parent ) :
  QObject(parent)
{
  m__Name = QString();
}

Group * Group_P::p_dptr() const
{
  return qobject_cast<Group *>( parent() );
}
