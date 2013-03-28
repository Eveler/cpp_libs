#include "officesstorage.h"

#include "office.h"


OfficesStorage *OfficesStorage::m__Instance = NULL;

OfficesStorage * OfficesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new OfficesStorage;

  return m__Instance;
}

QList<AbstractSimpleObject *> OfficesStorage::findByName(
    QList<AbstractSimpleObject *> objects, QString name )
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Office *office = qobject_cast<Office *>( object );
    if ( office->name() == name )
      result << object;
  }

  return result;
}

AbstractSimpleObject * OfficesStorage::createObject( QVariant id )
{
  return new Office( id, this );
}

OfficesStorage::OfficesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
