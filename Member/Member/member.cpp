#include "member.h"

#include "member_p.h"


Member::~Member()
{
  delete p;
  p = NULL;
}

const QString & Member::surname() const
{
  return p->m__Surname;
}

const QString & Member::firstname() const
{
  return p->m__Firstname;
}

const QString & Member::lastname() const
{
  return p->m__Lastname;
}

Post * Member::post() const
{
  return p->m__Post;
}

bool Member::active() const
{
  return p->m__Active;
}

bool Member::dismissed() const
{
  return p->m__Dismissed;
}

Group * Member::group() const
{
  return p->m__Group;
}

void Member::setSurname( const QString &surname )
{
  p->m__Surname = surname;
  emit surnameChanged();
}

void Member::setFirstname( const QString &firstname )
{
  p->m__Firstname = firstname;
  emit firstnameChanged();
}

void Member::setLastname( const QString &lastname )
{
  p->m__Lastname = lastname;
  emit lastnameChanged();
}

void Member::setPost( Post *post )
{
  p->setPost( post );
  emit postChaged();
}

void Member::setActive( bool active )
{
  p->m__Active = active;
  emit activeChanged();
}

void Member::setDismissed( bool value )
{
  p->m__Dismissed = value;
  emit dismissedChanged();
}

void Member::setGroup( Group *group )
{
  p->setGroup( group );
  emit groupChanged();
}

Member::Member( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new Member_P( this );
}

