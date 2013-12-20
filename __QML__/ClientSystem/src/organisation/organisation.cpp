#include "organisation.h"

#include "organisation_p.h"
#include "organisationlist.h"


#define INFO_REF OrganisationInfo *info = static_cast<OrganisationInfo *>( p->p_dptr() );

Organisation::Organisation( OrganisationList *parent ) :
  QObject(parent), OrganisationInfo()
{
  p = new Organisation_P( this );
}

Organisation::Organisation( OrganisationList *parent, const OrganisationInfo &info ) :
  QObject(parent), OrganisationInfo(info)
{
  p = new Organisation_P( this );
}

Organisation::Organisation( OrganisationList *parent, Organisation *link ) :
  QObject(parent), OrganisationInfo()
{
  p = new Organisation_P( this );

  if ( parent == NULL ) return;

  p->m__Link = link;
}

Organisation::~Organisation()
{
  delete p;
  p = NULL;
}

OrganisationList * Organisation::organisationList() const
{
  return qobject_cast<OrganisationList *>( parent() );
}

int Organisation::index() const
{
  OrganisationList *pl = organisationList();
  if ( pl == NULL ) return -1;

  return pl->organisationIndex( p->p_dptr() );
}

void Organisation::setOrganisationInfo( const OrganisationInfo &info )
{
  setIdentifier( info.identifier() );
  setFullname( info.fullname() );
  setHumanIdentifier( info.humanIdentifier() );
  setAddress( info.address() );
  setPhone( info.phone() );
  setEmail( info.email() );
}

QVariant Organisation::identifier() const
{
  if ( parent() == NULL ) return QVariant();

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->identifier();
  return info->identifier();
}

void Organisation::setIdentifier( QVariant identifier )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
  else info->setIdentifier( identifier );
  emit identifierChanged();
}

const QString & Organisation::fullname() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->fullname();
  return info->fullname();
}

void Organisation::setFullname( const QString &fullname )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setFullname( fullname );
  else info->setFullname( fullname );
  emit fullnameChanged();
}

QVariant Organisation::humanIdentifier() const
{
  if ( parent() == NULL ) return QVariant();

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->humanIdentifier();
  return info->humanIdentifier();
}

void Organisation::setHumanIdentifier( QVariant humanIdentifier )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setHumanIdentifier( humanIdentifier );
  else info->setHumanIdentifier( humanIdentifier );
  emit humanIdentifierChanged();
}

const QString & Organisation::address() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->address();
  return info->address();
}

void Organisation::setAddress( const QString &address )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setAddress( address );
  else info->setAddress( address );
  emit addressChanged();
}

const QString & Organisation::phone() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->phone();
  return info->phone();
}

void Organisation::setPhone( const QString &phone )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setPhone( phone );
  else info->setPhone( phone );
  emit phoneChanged();
}

const QString & Organisation::email() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->email();
  return info->email();
}

void Organisation::setEmail( const QString &email )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setEmail( email );
  else info->setEmail( email );
  emit emailChanged();
}
