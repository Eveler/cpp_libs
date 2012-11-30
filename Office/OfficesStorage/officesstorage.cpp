#include "officesstorage.h"

OfficesStorage *OfficesStorage::m__Instance = NULL;

OfficesStorage * OfficesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new OfficesStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & OfficesStorage::objects() const
{
  return m__Offices;
}

OfficesStorage::OfficesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void OfficesStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
}

void OfficesStorage::recordAdded( MFCRecord *record, int index )
{
  Office *office = new Office( this );
  setObjectData( office, record );
  m__Offices.insert( index, office );
}

void OfficesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  AbstractSimpleObject *obj = m__Offices.takeAt( index );
  delete obj;
}
