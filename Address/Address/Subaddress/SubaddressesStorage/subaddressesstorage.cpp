#include "subaddressesstorage.h"

#include "postcodesstorage.h"
#include "structurestatusesstorage.h"

SubaddressesStorage *SubaddressesStorage::m__Instance = NULL;

SubaddressesStorage * SubaddressesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new SubaddressesStorage;

  return m__Instance;
}

bool SubaddressesStorage::setStorage( StorageItemModel *stor, StructSubaddressCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.cId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cPostcode ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cHouseNumber ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cBuildNumber ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cStructNumber ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cStructureStatus ) == -1 )
    return false;

  m__Storage = stor;
  m__Cols = cols;

  connect( stor, SIGNAL(destroyed()),
           this, SLOT(storageDestroyed()) );
  connect( stor, SIGNAL(recordAdded(MFCRecord*,int)),
           this, SLOT(recordAdded(MFCRecord*,int)) );
  connect( stor, SIGNAL(recordRemoved(MFCRecord*,int)),
           this, SLOT(recordRemoved(MFCRecord*,int)) );
  connect( stor, SIGNAL(recordRemoved(MFCRecord*,int)),
           this, SLOT(disconnectRecord(MFCRecord*,int)) );

  for ( int rIdx = 0; rIdx < stor->availableRecords().count(); rIdx++ )
  {
    MFCRecord *record = stor->availableRecords()[rIdx];
    connect( record, SIGNAL(propertyChanged(QString)),
             this, SLOT(propertyChanged(QString)) );
    recordAdded( record, rIdx );
  }

  return true;
}

StorageItemModel * SubaddressesStorage::storage() const
{
  return m__Storage;
}

const QList<Subaddress *> & SubaddressesStorage::objects() const
{
  return m__Subaddresses;
}

QList<Subaddress *> SubaddressesStorage::findById( QList<Subaddress *> objs, QVariant value ) const
{
  QList<Subaddress *> result = QList<Subaddress *>();

  foreach ( Subaddress *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

SubaddressesStorage::SubaddressesStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

SubaddressesStorage::~SubaddressesStorage()
{
  reset();
}

void SubaddressesStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cPostcode.clear();
  m__Cols.cHouseNumber.clear();
  m__Cols.cBuildNumber.clear();
  m__Cols.cStructNumber.clear();
  m__Cols.cStructureStatus.clear();
}

void SubaddressesStorage::setObjectData( Subaddress *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  PostcodesStorage *postcodesStorage = PostcodesStorage::instance();
  QList<AbstractSimpleObject *> postcodes = postcodesStorage->find(
        postcodesStorage->objects(), record->currentProperty( m__Cols.cPostcode ) );
  if ( !postcodes.isEmpty() ) obj->setPostcode( postcodes.first() );
  obj->setHouseNumber( record->currentProperty( m__Cols.cHouseNumber ).toString() );
  obj->setBuildNumber( record->currentProperty( m__Cols.cBuildNumber ).toString() );
  obj->setStructNumber( record->currentProperty( m__Cols.cStructNumber ).toString() );
  StructureStatusesStorage *structureStatusesStorage = StructureStatusesStorage::instance();
  QList<StructureStatus *> structureStatuses = structureStatusesStorage->findById(
        structureStatusesStorage->objects(), record->currentProperty( m__Cols.cStructureStatus ) );
  if ( !structureStatuses.isEmpty() ) obj->setStructureStatus( structureStatuses.first() );
}

void SubaddressesStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void SubaddressesStorage::recordAdded( MFCRecord *record, int index )
{
  Subaddress *subaddress = new Subaddress( this );
  setObjectData( subaddress, record );
  m__Subaddresses.insert( index, subaddress );
}

void SubaddressesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Subaddresses.removeAt( index );
}

void SubaddressesStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void SubaddressesStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cPostcode &&
       column != m__Cols.cHouseNumber && column != m__Cols.cBuildNumber &&
       column != m__Cols.cStructNumber && column != m__Cols.cStructureStatus )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Subaddress *obj = objects()[index];
  setObjectData( obj, record );
}
