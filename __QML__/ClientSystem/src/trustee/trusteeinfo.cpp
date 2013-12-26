#include "trusteeinfo.h"


TrusteeInfo::TrusteeInfo() :
  m__Identifier(QVariant()),
  m__DeclarIdentifier(QVariant()),
  m__TrusteeClientIdentifier(QVariant()),
  m__ClientIdentifier(QVariant())
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

QVariant TrusteeInfo::trusteeClientIdentifier() const
{
  return m__TrusteeClientIdentifier;
}

void TrusteeInfo::setTrusteeClientIdentifier( QVariant trusteeClientIdentifier )
{
  m__TrusteeClientIdentifier = trusteeClientIdentifier;
}

QVariant TrusteeInfo::clientIdentifier() const
{
  return m__ClientIdentifier;
}

void TrusteeInfo::setClientIdentifier( QVariant clientIdentifier )
{
  m__ClientIdentifier = clientIdentifier;
}
