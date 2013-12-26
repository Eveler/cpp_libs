#include "departmentinfo.h"


DepartmentInfo::DepartmentInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

DepartmentInfo::DepartmentInfo( const DepartmentInfo &other ) :
  m__Identifier(other.identifier()),
  m__Name(other.name())
{
}

DepartmentInfo::~DepartmentInfo()
{
}

QVariant DepartmentInfo::identifier() const
{
  return m__Identifier;
}

void DepartmentInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QString DepartmentInfo::name() const
{
  return m__Name;
}

void DepartmentInfo::setName( QString name )
{
  m__Name = name;
}
