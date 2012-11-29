#include "destinationsstorage.h"

DestinationsStorage *DestinationsStorage::m__Instance = NULL;

DestinationsStorage * DestinationsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DestinationsStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & DestinationsStorage::objects() const
{
  return m__Destinations;
}

DestinationsStorage::DestinationsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void DestinationsStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__ColName_Id ) );
  obj->setName( record->currentProperty( m__ColName_Name ).toString() );
}

void DestinationsStorage::recordAdded( MFCRecord *record, int index )
{
  Destination *destination = new Destination( this );
  setObjectData( destination, record );
  m__Destinations.insert( index, destination );
}

void DestinationsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Destinations.removeAt( index );
}

