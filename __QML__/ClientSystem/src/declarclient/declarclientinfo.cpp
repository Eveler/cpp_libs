#include "declarclientinfo.h"


DeclarClientInfo::DeclarClientInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__DeclarIdentifier(QVariant()),
  m__ClientIdentifier(QVariant())
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
