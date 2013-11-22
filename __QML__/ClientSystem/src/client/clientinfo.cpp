#include "clientinfo.h"


ClientInfo::ClientInfo() :
  m__Identifier(QVariant()),
  m__OrganisationIdentifier(QVariant()),
  m__HumanIdentifier(QVariant())
{
}

ClientInfo::ClientInfo( const ClientInfo &other ) :
  m__Identifier(other.identifier()),
  m__OrganisationIdentifier(other.organisationIdentifier()),
  m__HumanIdentifier(other.humanIdentifier())
{
}

ClientInfo::~ClientInfo()
{
}

QVariant ClientInfo::identifier() const
{
  return m__Identifier;
}

void ClientInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QVariant ClientInfo::organisationIdentifier() const
{
  return m__OrganisationIdentifier;
}

void ClientInfo::setOrganisationIdentifier( QVariant organisationIdentifier )
{
  m__OrganisationIdentifier = organisationIdentifier;
}

QVariant ClientInfo::humanIdentifier() const
{
  return m__HumanIdentifier;
}

void ClientInfo::setHumanIdentifier( QVariant humanIdentifier )
{
  m__HumanIdentifier = humanIdentifier;
}
