#include "declarclientinfo.h"


DeclarClientInfo::DeclarClientInfo() :
  m__Identifier(QVariant()),
  m__DeclarIdentifier(QVariant()),
  m__ClientIdentifier(QVariant())
{
}

DeclarClientInfo::DeclarClientInfo( const DeclarClientInfo &other ) :
  m__Identifier(other.identifier()),
  m__DeclarIdentifier(other.declarIdentifier()),
  m__ClientIdentifier(other.clientIdentifier())
{
}

DeclarClientInfo::~DeclarClientInfo()
{
}

QVariant DeclarClientInfo::identifier() const
{
  return m__Identifier;
}

void DeclarClientInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QVariant DeclarClientInfo::declarIdentifier() const
{
  return m__DeclarIdentifier;
}

void DeclarClientInfo::setDeclarIdentifier( QVariant declarIdentifier )
{
  m__DeclarIdentifier = declarIdentifier;
}

QVariant DeclarClientInfo::clientIdentifier() const
{
  return m__ClientIdentifier;
}

void DeclarClientInfo::setClientIdentifier( QVariant clientIdentifier )
{
  m__ClientIdentifier = clientIdentifier;
}
