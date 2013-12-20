#include "trusteeinfo.h"


TrusteeInfo::TrusteeInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__DeclarIdentifier(QVariant()),
  m__ClientIdentifiers(QVariantList())
{
}

TrusteeInfo::~TrusteeInfo()
{
}

QVariant TrusteeInfo::identifier() const
{
  return m__Identifier;
}

void TrusteeInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QVariant TrusteeInfo::declarIdentifier() const
{
  return m__DeclarIdentifier;
}

void TrusteeInfo::setDeclarIdentifier( QVariant declarIdentifier )
{
  m__DeclarIdentifier = declarIdentifier;
}
QVariantList TrusteeInfo::clientIdentifiers() const
{
  return m__ClientIdentifiers;
}

void TrusteeInfo::addClientIdentifier( QVariant clientIdentifier )
{
  if ( !m__ClientIdentifiers.contains( clientIdentifier ) )
    m__ClientIdentifiers << clientIdentifier;
}

void TrusteeInfo::removeClientIdentifier( QVariant clientIdentifier )
{
  m__ClientIdentifiers.removeOne( clientIdentifier );
}

void TrusteeInfo::clearClientIdentifiers()
{
  m__ClientIdentifiers.clear();
}
