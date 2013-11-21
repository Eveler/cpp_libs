#include "service.h"

#include "service_p.h"
#include "servicelist.h"


#define INFO_REF ServiceInfo *info = static_cast<ServiceInfo *>( p->p_dptr() );

Service::Service( ServiceList *parent ) :
  QObject(parent), ServiceInfo()
{
  p = new Service_P( this );
}

Service::Service( ServiceList *parent, const ServiceInfo &info ) :
  QObject(parent), ServiceInfo(info)
{
  p = new Service_P( this );
}

Service::Service( ServiceList *parent, Service *link ) :
  QObject(parent), ServiceInfo()
{
  p = new Service_P( this );

  if ( parent == NULL ) return;

  p->m__Link = link;
}

Service::~Service()
{
  delete p;
  p = NULL;
}

ServiceList * Service::serviceList() const
{
  return qobject_cast<ServiceList *>( parent() );
}

int Service::index() const
{
  ServiceList *pl = serviceList();
  if ( pl == NULL ) return -1;

  return pl->serviceIndex( p->p_dptr() );
}

QVariant Service::identifier() const
{
  if ( parent() == NULL ) return QVariant();

  INFO_REF

      if ( p->m__Link != NULL ) return p->m__Link->identifier();
  return info->identifier();
}

void Service::setIdentifier( QVariant identifier )
{
  if ( parent() == NULL ) return;

  INFO_REF

      if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
  else info->setIdentifier( identifier );
  emit identifierChanged();
}

const QString & Service::name() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF

      if ( p->m__Link != NULL ) return p->m__Link->name();
  return info->name();
}

void Service::setName( const QString &name )
{
  if ( parent() == NULL ) return;

  INFO_REF

      if ( p->m__Link != NULL ) p->m__Link->setName( name );
  else info->setName( name );
  emit nameChanged();
}
