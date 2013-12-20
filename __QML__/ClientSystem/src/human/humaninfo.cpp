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

const QString & HumanInfo::surname() const
{
  return m__Surname;
}

void HumanInfo::setSurname( const QString &surname )
{
  m__Surname = surname;
}

const QString & HumanInfo::firstname() const
{
  return m__Firstname;
}

void HumanInfo::setFirstname( const QString &firstname )
{
  m__Firstname = firstname;
}

const QString & HumanInfo::lastname() const
{
  return m__Lastname;
}

void HumanInfo::setLastname( const QString &lastname )
{
  m__Lastname = lastname;
}

const QString & HumanInfo::address() const
{
  return m__Address;
}

void HumanInfo::setAddress( const QString &address )
{
  m__Address = address;
}

const QString & HumanInfo::phone() const
{
  return m__Phone;
}

void HumanInfo::setPhone( const QString &phone )
{
  m__Phone = phone;
}

const QString & HumanInfo::email() const
{
  return m__Email;
}

void HumanInfo::setEmail( const QString &email )
{
  m__Email = email;
}
