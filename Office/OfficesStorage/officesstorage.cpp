#include "officesstorage.h"

#include "office.h"


OfficesStorage *OfficesStorage::m__Instance = NULL;

OfficesStorage * OfficesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new OfficesStorage;

  return m__Instance;
}

const OfficeList & OfficesStorage::offices() const
{
  return *((OfficeList *)(&objects()));
}

AbstractSimpleObjectList OfficesStorage::findByName(
    AbstractSimpleObjectList objects, QString name )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
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
