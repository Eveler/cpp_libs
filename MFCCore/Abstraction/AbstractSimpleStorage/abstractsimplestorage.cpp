#include "abstractsimplestorage.h"

#include "abstractsimpleobject.h"


AbstractSimpleStorage::AbstractSimpleStorage(QObject *parent) :
  QObject(parent),
  m__Objects(QList<AbstractSimpleObject *>())
{
}

AbstractSimpleStorage::~AbstractSimpleStorage()
{
  clear();
}

AbstractSimpleObject * AbstractSimpleStorage::addObject( QVariant id )
{
  QList<AbstractSimpleObject *> objs = findById( objects(), id );
  if ( !objs.isEmpty() ) return objs.first();
  else
  {
    AbstractSimpleObject *object = createObject( id );
    connect( object, SIGNAL(destroyed(QObject*)), SLOT(objectDestroyed(QObject*)) );
    m__Objects << object;
    return object;
  }
}

const QList<AbstractSimpleObject *> & AbstractSimpleStorage::objects() const
{
  return m__Objects;
}

void AbstractSimpleStorage::clear()
{
  while ( !m__Objects.isEmpty() )
  {
    AbstractSimpleObject *object = m__Objects.takeFirst();
    disconnect( object, SIGNAL(destroyed(QObject*)), this, SLOT(objectDestroyed(QObject*)) );
    delete object;
    object = NULL;
  }
}

QList<AbstractSimpleObject *> AbstractSimpleStorage::findById(
    QList<AbstractSimpleObject *> objects, QVariant id ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *object, objects )
    if ( object->id() == id ) result << object;

  return result;
}

void AbstractSimpleStorage::objectDestroyed( QObject *object )
{
  AbstractSimpleObject *ob = (AbstractSimpleObject *)object;
  m__Objects.removeOne( ob );
}

