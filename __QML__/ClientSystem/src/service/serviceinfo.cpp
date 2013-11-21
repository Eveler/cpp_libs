#include "serviceinfo.h"


ServiceInfo::ServiceInfo() :
  m__Identifier(QVariant()),
  m__Name(QString())
{
}

ServiceInfo::ServiceInfo( const ServiceInfo &other ) :
  m__Identifier(other.identifier()),
  m__Root(other.root()),
  m__Sidx(other.sidx()),
  m__Name(other.name()),
  m__Deadline(other.deadline()),
  m__Workdays(other.workdays()),
  m__Isactive(other.isactive())
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

QVariant ServiceInfo::root() const
{
  return m__Root;
}

void ServiceInfo::setRoot( QVariant root )
{
  m__Root = root;
}

const QString & ServiceInfo::sidx() const
{
  return m__Sidx;
}

void ServiceInfo::setSidx( const QString &sidx )
{
  m__Sidx = sidx;
}

const QString & ServiceInfo::name() const
{
  return m__Name;
}

void ServiceInfo::setName( const QString &name )
{
  m__Name = name;
}

int ServiceInfo::deadline() const
{
  return m__Deadline;
}

void ServiceInfo::setDeadline( int deadline )
{
  m__Deadline = deadline;
}

bool ServiceInfo::workdays() const
{
  return m__Workdays;
}

void ServiceInfo::setWorkdays( bool workdays )
{
  m__Workdays = workdays;
}

bool ServiceInfo::isactive() const
{
  return m__Isactive;
}

void ServiceInfo::setIsactive( bool isactive )
{
  m__Isactive = isactive;
}
