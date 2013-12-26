#include "userinfo.h"


UserInfo::UserInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Surname(QString()),
  m__Firstname(QString()),
  m__Lastname(QString()),
  m__PostIdentifier(QVariant()),
  m__DepartmentIdentifier(QVariant()),
  m__Isactive(false),
  m__Dismissed(false),
  m__Dblogin(QString()),
  m__DirectionIdentifier(QVariant())
{
}

UserInfo::~UserInfo()
{
}

QVariant UserInfo::identifier() const
{
  return m__Identifier;
}

void UserInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QString UserInfo::surname() const
{
  return m__Surname;
}

void UserInfo::setSurname( QString surname )
{
  m__Surname = surname;
}

QString UserInfo::firstname() const
{
  return m__Firstname;
}

void UserInfo::setFirstname( QString firstname )
{
  m__Firstname = firstname;
}

QString UserInfo::lastname() const
{
  return m__Lastname;
}

void UserInfo::setLastname( QString lastname )
{
  m__Lastname = lastname;
}

QVariant UserInfo::postIdentifier() const
{
  return m__PostIdentifier;
}

void UserInfo::setPostIdentifier( QVariant postIdentifier )
{
  m__PostIdentifier = postIdentifier;
}

QVariant UserInfo::departmentIdentifier() const
{
  return m__DepartmentIdentifier;
}

void UserInfo::setDepartmentIdentifier( QVariant departmentIdentifier )
{
  m__DepartmentIdentifier = departmentIdentifier;
}

bool UserInfo::isactive() const
{
  return m__Isactive;
}

void UserInfo::setIsactive( bool isactive )
{
  m__Isactive = isactive;
}

bool UserInfo::dismissed() const
{
  return m__Dismissed;
}

void UserInfo::setDismissed( bool dismissed )
{
  m__Dismissed = dismissed;
}

QString UserInfo::dblogin() const
{
  return m__Dblogin;
}

void UserInfo::setDblogin( QString dblogin )
{
  m__Dblogin = dblogin;
}

QVariant UserInfo::directionIdentifier() const
{
  return m__DirectionIdentifier;
}

void UserInfo::setDirectionIdentifier( QVariant directionIdentifier )
{
  m__DirectionIdentifier = directionIdentifier;
}
