#include "service_p.h"


Service_P::Service_P(Service *parent) :
  QObject(parent),
  m__Link(NULL),
  m__NullString(QString())
{
}

Service * Service_P::p_dptr() const
{
  return qobject_cast<Service *>( parent() );
}
