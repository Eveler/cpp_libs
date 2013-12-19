#include "human.h"

#include "human_p.h"
#include "humanlist.h"


#define INFO_REF HumanInfo *info = static_cast<HumanInfo *>( p->p_dptr() );

Human::Human( HumanList *parent ) :
  QObject(parent), HumanInfo()
{
  p = new Human_P( this );
}

Human::Human( HumanList *parent, const HumanInfo &info ) :
  QObject(parent), HumanInfo(info)
{
  p = new Human_P( this );
}

Human::Human( HumanList *parent, Human *link ) :
  QObject(parent), HumanInfo()
{
  p = new Human_P( this );

  if ( parent == NULL ) return;

  p->m__Link = link;
}

Human::~Human()
{
  delete p;
  p = NULL;
}

HumanList * Human::humanList() const
{
  return qobject_cast<HumanList *>( parent() );
}

int Human::index() const
{
  HumanList *pl = humanList();
  if ( pl == NULL ) return -1;

  return pl->humanIndex( p->p_dptr() );
}

void Human::setHumanInfo( const HumanInfo &info )
{
  setIdentifier( info.identifier() );
  setSurname( info.surname() );
  setFirstname( info.firstname() );
  setLastname( info.lastname() );
  setAddress( info.address() );
  setPhone( info.phone() );
  setEmail( info.email() );
}

QVariant Human::identifier() const
{
  if ( parent() == NULL ) return QVariant();

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->identifier();
  return info->identifier();
}

void Human::setIdentifier( QVariant identifier )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
  else info->setIdentifier( identifier );
  emit identifierChanged();
}

const QString & Human::surname() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->surname();
  return info->surname();
}

void Human::setSurname( const QString &surname )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setSurname( surname );
  else info->setSurname( surname );
  emit surnameChanged();
}

const QString & Human::firstname() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->firstname();
  return info->firstname();
}

void Human::setFirstname( const QString &firstname )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setFirstname( firstname );
  else info->setFirstname( firstname );
  emit firstnameChanged();
}

const QString & Human::lastname() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->lastname();
  return info->lastname();
}

void Human::setLastname( const QString &lastname )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setLastname( lastname );
  else info->setLastname( lastname );
  emit lastnameChanged();
}

const QString & Human::address() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->address();
  return info->address();
}

void Human::setAddress( const QString &address )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setAddress( address );
  else info->setAddress( address );
  emit addressChanged();
}

const QString & Human::phone() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->phone();
  return info->phone();
}

void Human::setPhone( const QString &phone )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setPhone( phone );
  else info->setPhone( phone );
  emit phoneChanged();
}

const QString & Human::email() const
{
  if ( parent() == NULL ) return p->m__NullString;

  INFO_REF;

  if ( p->m__Link != NULL ) return p->m__Link->email();
  return info->email();
}

void Human::setEmail( const QString &email )
{
  if ( parent() == NULL ) return;

  INFO_REF;

  if ( p->m__Link != NULL ) p->m__Link->setEmail( email );
  else info->setEmail( email );
  emit emailChanged();
}
