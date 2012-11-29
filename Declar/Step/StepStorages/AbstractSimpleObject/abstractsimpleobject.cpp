#include "abstractsimpleobject.h"

AbstractSimpleObject::AbstractSimpleObject(QObject *parent) :
    QObject(parent)
{
  m__StructAbstractSimpleObject.m__Id = QVariant();
  m__StructAbstractSimpleObject.m__Name = QString();
}

const QVariant & AbstractSimpleObject::id() const
{
  return m__StructAbstractSimpleObject.m__Id;
}

const QString & AbstractSimpleObject::name() const
{
  return m__StructAbstractSimpleObject.m__Name;
}

void AbstractSimpleObject::setId( QVariant value )
{
  m__StructAbstractSimpleObject.m__Id = value;
}

void AbstractSimpleObject::setName( QString value )
{
  m__StructAbstractSimpleObject.m__Name = value;
}
