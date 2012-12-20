#include "addressesstorage.h"

#include "countriesstorage.h"
#include "subjectsstorage.h"
#include "regionsstorage.h"
#include "areasstorage.h"
#include "citiesstorage.h"
#include "innercitiesstorage.h"
#include "townshipsstorage.h"
#include "streetsstorage.h"
#include "subaddressesstorage.h"
#include "slaveaddressesstorage.h"
#include "postcodesstorage.h"

AddressesStorage *AddressesStorage::m__Instance = NULL;

AddressesStorage * AddressesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new AddressesStorage;

  return m__Instance;
}

bool AddressesStorage::setStorage( StorageItemModel *stor, StructAddressCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.cId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cCountry ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cSubject ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cRegion ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cArea ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cCity ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cInnerCity ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cTownship ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cStreet ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cSubaddress ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cSlaveAddress ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cPostcode ) == -1 )
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

StorageItemModel * AddressesStorage::storage() const
{
  return m__Storage;
}

const QList<Address *> & AddressesStorage::objects() const
{
  return m__Addresses;
}

AddressesStorage::AddressesStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

AddressesStorage::~AddressesStorage()
{
  reset();
}

void AddressesStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cCountry.clear();
  m__Cols.cSubject.clear();
  m__Cols.cRegion.clear();
  m__Cols.cArea.clear();
  m__Cols.cCity.clear();
  m__Cols.cInnerCity.clear();
  m__Cols.cTownship.clear();
  m__Cols.cStreet.clear();
  m__Cols.cSubaddress.clear();
  m__Cols.cSlaveAddress.clear();
  m__Cols.cPostcode.clear();
}

void AddressesStorage::setObjectData( Address *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );

  CountriesStorage *countriesStorage = CountriesStorage::instance();
  QList<AbstractSimpleObject *> countries = countriesStorage->find(
        countriesStorage->objects(), record->currentProperty( m__Cols.cCountry ) );
  if ( !countries.isEmpty() ) obj->setCountry( countries.first() );

  SubjectsStorage *subjectsStorage = SubjectsStorage::instance();
  QList<Subject *> subjects = subjectsStorage->findById(
        subjectsStorage->objects(), record->currentProperty( m__Cols.cSubject ) );
  if ( !subjects.isEmpty() ) obj->setSubject( subjects.first() );

  RegionsStorage *regionsStorage = RegionsStorage::instance();
  QList<Region *> regions = regionsStorage->findById(
        regionsStorage->objects(), record->currentProperty( m__Cols.cRegion ) );
  if ( !regions.isEmpty() ) obj->setRegion( regions.first() );

  AreasStorage *areasStorage = AreasStorage::instance();
  QList<Area *> areas = areasStorage->findById(
        areasStorage->objects(), record->currentProperty( m__Cols.cArea ) );
  if ( !areas.isEmpty() ) obj->setArea( areas.first() );

  CitiesStorage *citiesStorage = CitiesStorage::instance();
  QList<City *> cities = citiesStorage->findById(
        citiesStorage->objects(), record->currentProperty( m__Cols.cCity ) );
  if ( !cities.isEmpty() ) obj->setCity( cities.first() );

  InnerCitiesStorage *innerCitiesStorage = InnerCitiesStorage::instance();
  QList<InnerCity *> innerCities = innerCitiesStorage->findById(
        innerCitiesStorage->objects(), record->currentProperty( m__Cols.cInnerCity ) );
  if ( !innerCities.isEmpty() ) obj->setInnerCity( innerCities.first() );

  TownshipsStorage *townshipsStorage = TownshipsStorage::instance();
  QList<Township *> townships = townshipsStorage->findById(
        townshipsStorage->objects(), record->currentProperty( m__Cols.cTownship ) );
  if ( !townships.isEmpty() ) obj->setTownship( townships.first() );

  StreetsStorage *streetsStorage = StreetsStorage::instance();
  QList<Street *> streets = streetsStorage->findById(
        streetsStorage->objects(), record->currentProperty( m__Cols.cStreet ) );
  if ( !streets.isEmpty() ) obj->setStreet( streets.first() );

  SubaddressesStorage *subaddressesStorage = SubaddressesStorage::instance();
  QList<Subaddress *> subaddresses = subaddressesStorage->findById(
        subaddressesStorage->objects(), record->currentProperty( m__Cols.cSubaddress ) );
  if ( !subaddresses.isEmpty() ) obj->setSubaddress( subaddresses.first() );

  SlaveAddressesStorage *slaveAddressesStorage = SlaveAddressesStorage::instance();
  QList<AbstractSimpleObject *> slaveAddresses = slaveAddressesStorage->find(
        slaveAddressesStorage->objects(), record->currentProperty( m__Cols.cSlaveAddress ) );
  if ( !slaveAddresses.isEmpty() ) obj->setSlaveAddress( slaveAddresses.first() );

  PostcodesStorage *postcodesStorage = PostcodesStorage::instance();
  QList<AbstractSimpleObject *> postcodes = postcodesStorage->find(
        postcodesStorage->objects(), record->currentProperty( m__Cols.cPostcode ) );
  if ( !postcodes.isEmpty() ) obj->setPostalcode( postcodes.first() );
}

void AddressesStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void AddressesStorage::recordAdded( MFCRecord *record, int index )
{
  Address *address = new Address( this );
  setObjectData( address, record );
  m__Addresses.insert( index, address );
}

void AddressesStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Addresses.removeAt( index );
}

void AddressesStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void AddressesStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cCountry &&
       column != m__Cols.cSubject && column != m__Cols.cRegion &&
       column != m__Cols.cArea && column != m__Cols.cCity &&
       column != m__Cols.cInnerCity && column != m__Cols.cTownship &&
       column != m__Cols.cStreet && column != m__Cols.cSubaddress &&
       column != m__Cols.cSlaveAddress && column != m__Cols.cPostcode )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Address *obj = objects()[index];
  setObjectData( obj, record );
}
