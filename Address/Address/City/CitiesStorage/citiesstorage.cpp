#include "citiesstorage.h"

#include "abbreviationsstorage.h"

CitiesStorage *CitiesStorage::m__Instance = NULL;

CitiesStorage * CitiesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new CitiesStorage;

  return m__Instance;
}

bool CitiesStorage::setStorage( StorageItemModel *stor, StructCityCols cols )
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

StorageItemModel * CitiesStorage::storage() const
{
  return m__Storage;
}

const QList<City *> & CitiesStorage::objects() const
{
  return m__Citie;
}

QList<City *> CitiesStorage::findById( QList<City *> objs, QVariant value ) const
{
  QList<City *> result = QList<City *>();

  foreach ( City *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

CitiesStorage::CitiesStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

CitiesStorage::~CitiesStorage()
{
  reset();
}

void CitiesStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void CitiesStorage::setObjectData( City *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void CitiesStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void CitiesStorage::recordAdded( MFCRecord *record, int index )
{
  City *city = new City( this );
  setObjectData( city, record );
  m__Citie.insert( index, city );
  connect( city, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( city, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void CitiesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Citie.removeAt( index );
}

void CitiesStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void CitiesStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  City *obj = objects()[index];
  setObjectData( obj, record );
}

void CitiesStorage::changedAbbreviation( Abbreviation *value )
{
  City *obj = qobject_cast<City *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void CitiesStorage::changedName( QString value )
{
  City *obj = qobject_cast<City *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
