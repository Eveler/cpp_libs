#include "service.h"

Service::Service(QObject *parent) :
    QObject(parent)
{
  m__StructService.m__Id = QVariant();
  m__StructService.m__Name = QString();
  m__StructService.m__Deadline = 0;
  m__StructService.m__Active = false;
}

const QVariant & Service::id() const
{
  return m__StructService.m__Id;
}

const QString & Service::name() const
{
  return m__StructService.m__Name;
}

const int & Service::deadline() const
{
  return m__StructService.m__Deadline;
}

bool Service::active() const
{
  return m__StructService.m__Active;
}

void Service::setId( QVariant value )
{
  m__StructService.m__Id = value;
}

void Service::setName( QString value )
{
  m__StructService.m__Name = value;
}

void Service::setDeadline( int value )
{
  m__StructService.m__Deadline = value;
}

void Service::setActive( bool value )
{
  m__StructService.m__Active = value;
}

