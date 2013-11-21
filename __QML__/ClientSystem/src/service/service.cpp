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

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->identifier();
  return info->identifier();
}

void Service::setIdentifier( QVariant identifier )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
  else info->setIdentifier( identifier );
  emit identifierChanged();
}

QVariant Service::root() const
{
  if ( parent() == NULL ) return QVariant();

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->root();
  return info->root();
}

void Service::setRoot( QVariant root )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setRoot( root );
  else info->setRoot( root );
  emit rootChanged();
}

const QString & Service::sidx() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->sidx();
  return info->sidx();
}

void Service::setSidx( const QString &sidx )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setSidx( sidx );
  else info->setSidx( sidx );
  emit sidxChanged();
}

const QString & Service::name() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->name();
  return info->name();
}

void Service::setName( const QString &name )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setName( name );
  else info->setName( name );
  emit nameChanged();
}

int Service::deadline() const
{
  if ( parent() == NULL ) return 0;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->deadline();
  return info->deadline();
}

void Service::setDeadline( int deadline )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setDeadline( deadline );
  else info->setDeadline( deadline );
  emit deadlineChanged();
}

bool Service::workdays() const
{
  if ( parent() == NULL ) return false;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->workdays();
  return info->workdays();
}

void Service::setWorkdays( bool workdays )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setWorkdays( workdays );
  else info->setWorkdays( workdays );
  emit workdaysChanged();
}

bool Service::isactive() const
{
  if ( parent() == NULL ) return false;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->isactive();
  return info->isactive();
}

void Service::setIsactive( bool isactive )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setIsactive( isactive );
  else info->setIsactive( isactive );
  emit isactiveChanged();
}

