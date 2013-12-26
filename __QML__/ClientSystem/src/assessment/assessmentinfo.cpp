#include "assessmentinfo.h"


AssessmentInfo::AssessmentInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
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

QString AssessmentInfo::name() const
{
  return m__Name;
}

void AssessmentInfo::setName( QString name )
{
  m__Name = name;
}
