#include "resultwayinfo.h"


ResultwayInfo::ResultwayInfo() :
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

ResultwayInfo::ResultwayInfo( const ResultwayInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

ResultwayInfo::~ResultwayInfo()
{
}

QVariant ResultwayInfo::identifier() const
{
  return m__Identifier;
}

void ResultwayInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & ResultwayInfo::name() const
{
  return m__Name;
}

void ResultwayInfo::setName( const QString &name )
{
  m__Name = name;
}
