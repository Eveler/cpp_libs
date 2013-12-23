#include "list.h"

#include <QDebug>


List::List(QQuickItem *parent) :
  QQuickItem(parent)
{
}

List::~List()
{
  while ( !m__Objects.isEmpty() )
  {
    QObject *obj = m__Objects.takeFirst();
    disconnect( obj, SIGNAL(destroyed(QObject*)), this, SLOT(objectDestroyed(QObject*)) );
    obj = NULL;
  }
}

QString List::propertyName() const
{
  return m__PropertyName;
}

void List::setPropertyName( QString propertyName )
{
  if ( m__Objects.isEmpty() )
  {
    m__PropertyName = propertyName;
    emit propertyNameChanged();
  }
}

QString List::specialObjects() const
{
  return m__SpecialObjects;
}

void List::setSpecialObjects( QString specialObjects )
{
  m__SpecialObjects = specialObjects;
  emit specialObjectsChanged();
}

int List::length() const
{
  return m__Objects.count();
}

QList<QObject *> List::model() const
{
  return m__Objects;
}

void List::append( QObject *obj )
{
  if ( m__Objects.contains( obj ) ||
       ( !m__SpecialObjects.isEmpty() &&
         obj->metaObject()->className() != m__SpecialObjects ) ) return;

//  if ( obj->dynamicPropertyNames().contains( m__PropertyName ) )
  connect( obj, SIGNAL(destroyed(QObject*)), SLOT(objectDestroyed(QObject*)) );
  m__Objects << obj;
  emit modelChanged();
  emit lengthChanged();
}

void List::remove( QObject *obj )
{
  if ( !m__Objects.contains( obj ) ) return;

  disconnect( obj, SIGNAL(destroyed(QObject*)), this, SLOT(objectDestroyed(QObject*)) );
  m__Objects.removeOne( obj );
  emit modelChanged();
  emit lengthChanged();
}

QObject * List::takeFirst()
{
  return m__Objects.takeFirst();
}

void List::objectDestroyed( QObject *obj )
{
  m__Objects.removeOne( obj );
  emit modelChanged();
  emit lengthChanged();
}
