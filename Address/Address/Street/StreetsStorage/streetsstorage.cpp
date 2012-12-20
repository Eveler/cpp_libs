#include "streetsstorage.h"

#include "abbreviationsstorage.h"

StreetsStorage *StreetsStorage::m__Instance = NULL;

StreetsStorage * StreetsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new StreetsStorage;

  return m__Instance;
}

bool StreetsStorage::setStorage( StorageItemModel *stor, StructStreetCols cols )
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

StorageItemModel * StreetsStorage::storage() const
{
  return m__Storage;
}

const QList<Street *> & StreetsStorage::objects() const
{
  return m__Streets;
}

QList<Street *> StreetsStorage::findById( QList<Street *> objs, QVariant value ) const
{
  QList<Street *> result = QList<Street *>();

  foreach ( Street *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

StreetsStorage::StreetsStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

StreetsStorage::~StreetsStorage()
{
  reset();
}

void StreetsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void StreetsStorage::setObjectData( Street *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void StreetsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void StreetsStorage::recordAdded( MFCRecord *record, int index )
{
  Street *street = new Street( this );
  setObjectData( street, record );
  m__Streets.insert( index, street );
  connect( street, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( street, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void StreetsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Streets.removeAt( index );
}

void StreetsStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void StreetsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Street *obj = objects()[index];
  setObjectData( obj, record );
}

void StreetsStorage::changedAbbreviation( Abbreviation *value )
{
  Street *obj = qobject_cast<Street *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void StreetsStorage::changedName( QString value )
{
  Street *obj = qobject_cast<Street *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
