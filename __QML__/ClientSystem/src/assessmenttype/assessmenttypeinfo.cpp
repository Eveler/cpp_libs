#include "assessmenttypeinfo.h"


AssessmenttypeInfo::AssessmenttypeInfo() :
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

AssessmenttypeInfo::AssessmenttypeInfo( const AssessmenttypeInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

AssessmenttypeInfo::~AssessmenttypeInfo()
{
}

QVariant AssessmenttypeInfo::identifier() const
{
  return m__Identifier;
}

void AssessmenttypeInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & AssessmenttypeInfo::name() const
{
  return m__Name;
}

void AssessmenttypeInfo::setName( const QString &name )
{
  m__Name = name;
}
