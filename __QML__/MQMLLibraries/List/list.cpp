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
  if ( m__Objects.contains( obj ) ) return;

  qDebug() << obj->metaObject()->className();

//  if ( obj->dynamicPropertyNames().contains( m__PropertyName ) )
}

void List::remove( QObject *obj )
{

}

QObject * List::takeFirst()
{

}

void List::objectDestroyed( QObject *obj )
{

}
