#include "assessmenttypeinfo.h"


AssessmenttypeInfo::AssessmenttypeInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
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

QString AssessmenttypeInfo::name() const
{
  return m__Name;
}

void AssessmenttypeInfo::setName( QString name )
{
  m__Name = name;
}
