#include "townshipsstorage.h"

#include "abbreviationsstorage.h"

TownshipsStorage *TownshipsStorage::m__Instance = NULL;

TownshipsStorage * TownshipsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new TownshipsStorage;

  return m__Instance;
}

bool TownshipsStorage::setStorage( StorageItemModel *stor, StructTownshipCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.cId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cAbbreviation ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cName ) == -1 )
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

StorageItemModel * TownshipsStorage::storage() const
{
  return m__Storage;
}

const QList<Township *> & TownshipsStorage::objects() const
{
  return m__Townships;
}

QList<Township *> TownshipsStorage::findById( QList<Township *> objs, QVariant value ) const
{
  QList<Township *> result = QList<Township *>();

  foreach ( Township *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

TownshipsStorage::TownshipsStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

TownshipsStorage::~TownshipsStorage()
{
  reset();
}

void TownshipsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void TownshipsStorage::setObjectData( Township *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void TownshipsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void TownshipsStorage::recordAdded( MFCRecord *record, int index )
{
  Township *township = new Township( this );
  setObjectData( township, record );
  m__Townships.insert( index, township );
}

void TownshipsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Townships.removeAt( index );
}

void TownshipsStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void TownshipsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Township *obj = objects()[index];
  setObjectData( obj, record );
}
