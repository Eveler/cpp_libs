#include "servicesstorage.h"

ServicesStorage *ServicesStorage::m__Instance = NULL;

ServicesStorage * ServicesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new ServicesStorage;

  return m__Instance;
}

bool ServicesStorage::setStorage( StorageItemModel *stor, StructServiceCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.Id ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Name ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Deadline ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Active ) == -1 )
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

StorageItemModel * ServicesStorage::storage() const
{
  return m__Storage;
}

const QList<Service *> & ServicesStorage::objects() const
{
  return m__Services;
}

ServicesStorage::ServicesStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

ServicesStorage::~ServicesStorage()
{
  reset();
}

void ServicesStorage::reset()
{
  m__Storage = NULL;
  m__Cols.Id.clear();
  m__Cols.Name.clear();
  m__Cols.Deadline.clear();
  m__Cols.Active.clear();
}

void ServicesStorage::setObjectData( Service *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
  obj->setDeadline( record->currentProperty( m__Cols.Deadline ).toInt() );
  obj->setActive( record->currentProperty( m__Cols.Active ).toBool() );
}

void ServicesStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void ServicesStorage::recordAdded( MFCRecord *record, int index )
{
  Service *service = new Service( this );
  setObjectData( service, record );
  m__Services.insert( index, service );
}

void ServicesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Services.removeAt( index );
}

void ServicesStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void ServicesStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.Id && column != m__Cols.Name &&
       column != m__Cols.Deadline && column != m__Cols.Active )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Service *obj = objects()[index];
  setObjectData( obj, record );
}
