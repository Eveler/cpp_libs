#include "abstractsimpleobject.h"

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

void AbstractSimpleObject::setName( QString value )
{
  if ( m__Value.m__Name == value ) return;

  m__Value.m__Name = value;
  emit changedName( value );
}

AbstractSimpleObject::AbstractSimpleObject( QVariant id, QObject *parent ) :
    QObject(parent)
{
  clear();
  setId( id );
}

void AbstractSimpleObject::clear()
{
  m__Value.m__Id = QVariant();
  m__Value.m__Name = QString();
}

void AbstractSimpleObject::setId( QVariant value )
{
  m__Value.m__Id = value;
}

