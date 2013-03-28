#include "user.h"

#include "user_p.h"


User::~User()
{
  delete p;
  p = NULL;
}

const QString & User::surname() const
{
  return p->m__Surname;
}

const QString & User::firstname() const
{
  return p->m__Firstname;
}

const QString & User::lastname() const
{
  return p->m__Lastname;
}

Post * User::post() const
{
  return p->m__Post;
}

Department * User::department() const
{
  return p->m__Department;
}

bool User::active() const
{
  return p->m__Active;
}

bool User::dismissed() const
{
  return p->m__Dismissed;
}

Office * User::office() const
{
  return p->m__Office;
}

Group * User::group() const
{
  return p->m__Group;
}

void User::setSurname( const QString &surname )
{
  p->m__Surname = surname;
  emit surnameChanged();
}

void User::setFirstname( const QString &firstname )
{
  p->m__Firstname = firstname;
  emit firstnameChanged();
}

void User::setLastname( const QString &lastname )
{
  p->m__Lastname = lastname;
  emit lastnameChanged();
}

void User::setPost( Post *post )
{
  p->m__Post = post;
  emit postChaged();
}

void User::setDepartment( Department *department )
{
  p->m__Department = department;
  emit departmentChanged();
}

void User::setActive( bool active )
{
  p->m__Active = active;
  emit activeChanged();
}

void User::setDismissed( bool value )
{
  p->m__Dismissed = value;
  emit dismissedChanged();
}

void User::setOffice( Office *office )
{
  p->m__Office = office;
  emit officeChanged();
}

void User::setGroup( Group *group )
{
  p->m__Group = group;
  emit groupChanged();
}

User::User( QVariant id, QObject *parent ) :
  AbstractSimpleObject(id, parent)
{
  p = new User_P( this );
}

