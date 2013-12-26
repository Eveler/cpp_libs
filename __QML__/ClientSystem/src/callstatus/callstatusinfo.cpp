#include "callstatusinfo.h"


CallstatusInfo::CallstatusInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

CallstatusInfo::~CallstatusInfo()
{
}

QVariant CallstatusInfo::identifier() const
{
  return m__Identifier;
}

void CallstatusInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QString CallstatusInfo::name() const
{
  return m__Name;
}

void CallstatusInfo::setName( QString name )
{
  m__Name = name;
}
