#include "user.h"

User::User(QObject *parent) :
    QObject(parent)
{
  clear();
}

User::~User()
{
  clear();
}

const QVariant & User::id() const
{
  return m__User.m__Id;
}

const StructName & User::name() const
{
  return m__User.m__Name;
}

const Post * User::post() const
{
  return m__User.m__Post;
}

const Department * User::department() const
{
  return m__User.m__Department;
}

const bool User::active() const
{
  return m__User.m__Active;
}

const bool User::dismissed() const
{
  return m__User.m__Dismissed;
}

const Office * User::office() const
{
  return m__User.m__Office;
}

void User::clear()
{
  StructName sName = {QString(), QString(), QString()};
  m__User.m__Id = QVariant();
  m__User.m__Name = sName;
  m__User.m__Post = NULL;
  m__User.m__Department = NULL;
  m__User.m__Active = false;
  m__User.m__Dismissed = false;
  m__User.m__Office = NULL;
}

void User::setId( QVariant value )
{
  m__User.m__Id = value;
}

void User::setName( StructName value )
{
  m__User.m__Name = value;
}

void User::setPost( Post *value )
{
  m__User.m__Post = value;
}

void User::setDepartment( Department *value )
{
  m__User.m__Department = value;
}

void User::setActive( bool value )
{
  m__User.m__Active = value;
}

void User::setDismissed( bool value )
{
  m__User.m__Dismissed = value;
}

void User::setOffice( Office *value )
{
  m__User.m__Office = value;
}

