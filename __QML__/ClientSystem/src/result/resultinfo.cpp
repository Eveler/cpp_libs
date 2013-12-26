#include "resultinfo.h"


ResultInfo::ResultInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

ResultInfo::~ResultInfo()
{
}

QVariant ResultInfo::identifier() const
{
  return m__Identifier;
}

void ResultInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QString ResultInfo::name() const
{
  return m__Name;
}

void ResultInfo::setName( QString name )
{
  m__Name = name;
}
