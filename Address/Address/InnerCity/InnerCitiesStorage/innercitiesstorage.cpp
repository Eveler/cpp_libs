#include "innercitiesstorage.h"

#include "abbreviationsstorage.h"

InnerCitiesStorage *InnerCitiesStorage::m__Instance = NULL;

InnerCitiesStorage * InnerCitiesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new InnerCitiesStorage;

  return m__Instance;
}

bool InnerCitiesStorage::setStorage( StorageItemModel *stor, StructInnerCitieCols cols )
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

StorageItemModel * InnerCitiesStorage::storage() const
{
  return m__Storage;
}

const QList<InnerCity *> & InnerCitiesStorage::objects() const
{
  return m__InnerCities;
}

QList<InnerCity *> InnerCitiesStorage::findById( QList<InnerCity *> objs, QVariant value ) const
{
  QList<InnerCity *> result = QList<InnerCity *>();

  foreach ( InnerCity *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

InnerCitiesStorage::InnerCitiesStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

InnerCitiesStorage::~InnerCitiesStorage()
{
  reset();
}

void InnerCitiesStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void InnerCitiesStorage::setObjectData( InnerCity *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void InnerCitiesStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void InnerCitiesStorage::recordAdded( MFCRecord *record, int index )
{
  InnerCity *innerCity= new InnerCity( this );
  setObjectData( innerCity, record );
  m__InnerCities.insert( index, innerCity);
  connect( innerCity, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( innerCity, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void InnerCitiesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__InnerCities.removeAt( index );
}

void InnerCitiesStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void InnerCitiesStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  InnerCity *obj = objects()[index];
  setObjectData( obj, record );
}

void InnerCitiesStorage::changedAbbreviation( Abbreviation *value )
{
  InnerCity *obj = qobject_cast<InnerCity *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void InnerCitiesStorage::changedName( QString value )
{
  InnerCity *obj = qobject_cast<InnerCity *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
