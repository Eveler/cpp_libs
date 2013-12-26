#include "humaninfo.h"


HumanInfo::HumanInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Surname(QString()),
  m__Firstname(QString()),
  m__Lastname(QString()),
  m__Address(QString()),
  m__Phone(QString()),
  m__Email(QString())
{
}

HumanInfo::~HumanInfo()
{
}

QVariant HumanInfo::identifier() const
{
  return m__Identifier;
}

void HumanInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QString HumanInfo::surname() const
{
  return m__Surname;
}

void HumanInfo::setSurname( QString surname )
{
  m__Surname = surname;
}

QString HumanInfo::firstname() const
{
  return m__Firstname;
}

void HumanInfo::setFirstname( QString firstname )
{
  m__Firstname = firstname;
}

QString HumanInfo::lastname() const
{
  return m__Lastname;
}

void HumanInfo::setLastname( QString lastname )
{
  m__Lastname = lastname;
}

QString HumanInfo::address() const
{
  return m__Address;
}

void HumanInfo::setAddress( QString address )
{
  m__Address = address;
}

QString HumanInfo::phone() const
{
  return m__Phone;
}

void HumanInfo::setPhone( QString phone )
{
  m__Phone = phone;
}

QString HumanInfo::email() const
{
  return m__Email;
}

void HumanInfo::setEmail( QString email )
{
  m__Email = email;
}
