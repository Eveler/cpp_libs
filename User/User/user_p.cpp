#include "user_p.h"

#include "user.h"


User_P::User_P( User *parent ) :
  QObject(parent)
{
  m__Surname = QString();
  m__Firstname = QString();
  m__Lastname = QString();
  m__Post = NULL;
  m__Department = NULL;
  m__Active = false;
  m__Dismissed = false;
  m__Office = NULL;
  m__Group = NULL;
}

User * User_P::p_dptr() const
{
  return qobject_cast<User *>( parent() );
}
