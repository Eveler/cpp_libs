#include "regionsstorage.h"

#include "abbreviationsstorage.h"

RegionsStorage *RegionsStorage::m__Instance = NULL;

RegionsStorage * RegionsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new RegionsStorage;

  return m__Instance;
}

bool RegionsStorage::setStorage( StorageItemModel *stor, StructRegionCols cols )
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

StorageItemModel * RegionsStorage::storage() const
{
  return m__Storage;
}

const QList<Region *> & RegionsStorage::objects() const
{
  return m__Regions;
}

QList<Region *> RegionsStorage::findById( QList<Region *> objs, QVariant value ) const
{
  QList<Region *> result = QList<Region *>();

  foreach ( Region *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

RegionsStorage::RegionsStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

RegionsStorage::~RegionsStorage()
{
  reset();
}

void RegionsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void RegionsStorage::setObjectData( Region *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void RegionsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void RegionsStorage::recordAdded( MFCRecord *record, int index )
{
  Region *region = new Region( this );
  setObjectData( region, record );
  m__Regions.insert( index, region );
  connect( region, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( region, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void RegionsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Regions.removeAt( index );
}

void RegionsStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void RegionsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Region *obj = objects()[index];
  setObjectData( obj, record );
}

void RegionsStorage::changedAbbreviation( Abbreviation *value )
{
  Region *obj = qobject_cast<Region *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void RegionsStorage::changedName( QString value )
{
  Region *obj = qobject_cast<Region *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
