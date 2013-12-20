#include "doctypeinfo.h"


DoctypeInfo::DoctypeInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

DoctypeInfo::DoctypeInfo( const DoctypeInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

DoctypeInfo::~DoctypeInfo()
{
}

QVariant DoctypeInfo::identifier() const
{
  return m__Identifier;
}

void DoctypeInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

const QString & DoctypeInfo::name() const
{
  return m__Name;
}

void DoctypeInfo::setName( const QString &name )
{
  m__Name = name;
}
