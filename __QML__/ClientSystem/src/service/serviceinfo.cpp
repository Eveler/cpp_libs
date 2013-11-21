#include "serviceinfo.h"


ServiceInfo::ServiceInfo() :
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

ServiceInfo::ServiceInfo( const ServiceInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

ServiceInfo::~ServiceInfo()
{
}

QVariant ServiceInfo::identifier() const
{
  return m__Identifier;
}

void ServiceInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & ServiceInfo::name() const
{
  return m__Name;
}

void ServiceInfo::setName( const QString &name )
{
  m__Name = name;
}
