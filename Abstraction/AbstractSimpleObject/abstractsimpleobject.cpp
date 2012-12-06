#include "abstractsimpleobject.h"

AbstractSimpleObject::AbstractSimpleObject(QObject *parent) :
    QObject(parent)
{
  clear();
}

AbstractSimpleObject::~AbstractSimpleObject()
{
  clear();
}

const QVariant & AbstractSimpleObject::id() const
{
  return m__Value.m__Id;
}

const QString & AbstractSimpleObject::name() const
{
  return m__Value.m__Name;
}

void AbstractSimpleObject::clear()
{
  setId( QVariant() );
  setName( QString() );
}

void AbstractSimpleObject::setId( QVariant value )
{
  m__Value.m__Id = value;
}

void AbstractSimpleObject::setName( QString value )
{
  m__Value.m__Name = value;
}
