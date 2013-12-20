#include "serviceinfo.h"


ServiceInfo::ServiceInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Root(QVariant()),
  m__Sidx(QString()),
  m__Name(QString()),
  m__Deadline(0),
  m__Workdays(false),
  m__Isactive(false)
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
