#include "servicelist.h"

#include "servicelist_p.h"


ServiceList::ServiceList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new ServiceList_P( this );
}

ServiceList::~ServiceList()
{
  while ( !p->m__Services.isEmpty() )
  {
    Service *service = p->m__Services.takeFirst();
    disconnect( service, SIGNAL(destroyed()), this, SLOT(serviceDestroyed()) );
    delete service;
    service = NULL;
  }

  delete p;
  p = NULL;
}

int ServiceList::count() const
{
  return p->m__Services.count();
}

void ServiceList::clear() const
{
  while ( !p->m__Services.isEmpty() )
  {
    Service *service = p->m__Services.takeFirst();
    disconnect( service, SIGNAL(destroyed()), this, SLOT(serviceDestroyed()) );
    delete service;
    service = NULL;
  }
  emit countChanged();
}

Service * ServiceList::service( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Services[index];
}

int ServiceList::serviceIndex( Service *service ) const
{
  return p->m__Services.indexOf( service );
}

Service * ServiceList::addLink( Service *link ) const
{
  if ( p->m__Services.contains( link ) ) return link;

  Service *newService = new Service( p->p_dptr(), link );
  p->m__Services << newService;
  connect( newService, SIGNAL(destroyed()), SLOT(serviceDestroyed()) );
  emit serviceAdded( newService );
  emit countChanged();
  return newService;
}

Service * ServiceList::find( QVariant identifier ) const
{
  foreach ( Service *service, p->m__Services )
    if ( service->identifier() == identifier ) return service;

  return NULL;
}

void ServiceList::receivedServiceInfo(ServiceInfo serviceInfo ) const
{
  Service *newService = new Service( p->p_dptr(), serviceInfo );
  p->m__Services << newService;
  connect( newService, SIGNAL(destroyed()), SLOT(serviceDestroyed()) );
  emit serviceAdded( newService );
  emit countChanged();
}

void ServiceList::serviceDestroyed()
{
  Service *service = qobject_cast<Service *>( sender() );
  int index = p->m__Services.indexOf( service );
  p->m__Services.removeAt( index );
  emit serviceRemoved( index );
  emit countChanged();
}
