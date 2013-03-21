#include "user.h"

User::~User()
{
  clear();
}

const QVariant & User::id() const
{
  return m__Value.m__Id;
}

const StructName & User::name() const
{
  return m__Value.m__Name;
}

const AbstractSimpleObject * User::post() const
{
  return m__Value.m__Post;
}

const AbstractSimpleObject * User::department() const
{
  return m__Value.m__Department;
}

bool User::active() const
{
  return m__Value.m__Active;
}

bool User::dismissed() const
{
  return m__Value.m__Dismissed;
}

const AbstractSimpleObject * User::office() const
{
  return m__Value.m__Office;
}

void User::setName( StructName value )
{
  m__Value.m__Name = value;
}

void User::setPost( AbstractSimpleObject *value )
{
  m__Value.m__Post = value;
}

void User::setDepartment( AbstractSimpleObject *value )
{
  m__Value.m__Department = value;
}

void User::setActive( bool value )
{
  m__Value.m__Active = value;
}

void User::setDismissed( bool value )
{
  m__Value.m__Dismissed = value;
}

void User::setOffice( AbstractSimpleObject *value )
{
  m__Value.m__Office = value;
}

User::User( QVariant id, QObject *parent ) :
    QObject(parent)
{
  clear();
}

void User::clear()
{
  StructName sName = {QString(), QString(), QString()};
  setId( QVariant() );
  setName( sName );
  setPost( NULL );
  setDepartment( NULL );
  setActive( false );
  setDismissed( false );
  setOffice( NULL );
}

void User::setId( QVariant value )
{
  m__Value.m__Id = value;
}

