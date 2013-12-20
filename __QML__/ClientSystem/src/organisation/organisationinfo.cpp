#include "organisationinfo.h"


OrganisationInfo::OrganisationInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Fullname(QString()),
  m__HumanIdentifier(QVariant()),
  m__Address(QString()),
  m__Phone(QString()),
  m__Email(QString())
{
}

OrganisationInfo::~OrganisationInfo()
{
}

QVariant OrganisationInfo::identifier() const
{
  return m__Identifier;
}

void OrganisationInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & OrganisationInfo::fullname() const
{
  return m__Fullname;
}

void OrganisationInfo::setFullname( const QString &fullname )
{
  m__Fullname = fullname;
}

QVariant OrganisationInfo::humanIdentifier() const
{
  return m__HumanIdentifier;
}

void OrganisationInfo::setHumanIdentifier( QVariant humanIdentifier )
{
  m__HumanIdentifier = humanIdentifier;
}

const QString & OrganisationInfo::address() const
{
  return m__Address;
}

void OrganisationInfo::setAddress( const QString &address )
{
  m__Address = address;
}

const QString & OrganisationInfo::phone() const
{
  return m__Phone;
}

void OrganisationInfo::setPhone( const QString &phone )
{
  m__Phone = phone;
}

const QString & OrganisationInfo::email() const
{
  return m__Email;
}

void OrganisationInfo::setEmail( const QString &email )
{
  m__Email = email;
}
