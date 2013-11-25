#include "assessmentinfo.h"


AssessmentInfo::AssessmentInfo() :
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

AssessmentInfo::AssessmentInfo( const AssessmentInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

AssessmentInfo::~AssessmentInfo()
{
}

QVariant AssessmentInfo::identifier() const
{
  return m__Identifier;
}

void AssessmentInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & AssessmentInfo::name() const
{
  return m__Name;
}

void AssessmentInfo::setName( const QString &name )
{
  m__Name = name;
}
