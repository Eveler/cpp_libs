#include "address.h"

Address::Address(QObject *parent) :
    QObject(parent)
{
  m__StructAddress.m__Id = QVariant();
}

const QVariant & Address::id() const
{
  return m__StructAddress.m__Id;
}

AbstractSimpleObject * Address::country() const
{
  return m__StructAddress.m__Country;
}

Subject * Address::subject() const
{
  return m__StructAddress.m__Subject;
}

Region * Address::region() const
{
  return m__StructAddress.m__Region;
}

Area * Address::area() const
{
  return m__StructAddress.m__Area;
}

City * Address::city() const
{
  return m__StructAddress.m__City;
}

InnerCity * Address::innerCity() const
{
  return m__StructAddress.m__InnerCity;
}

Township * Address::township() const
{
  return m__StructAddress.m__Township;
}

Street * Address::street() const
{
  return m__StructAddress.m__Street;
}

Subaddress * Address::subaddress() const
{
  return m__StructAddress.m__Subaddress;
}

AbstractSimpleObject * Address::slaveaddress() const
{
  return m__StructAddress.m__Slaveaddress;
}

AbstractSimpleObject * Address::postalcode() const
{
  return m__StructAddress.m__Postcode;
}

void Address::setId( QVariant value )
{
  m__StructAddress.m__Id = value;
}

void Address::setCountry( AbstractSimpleObject *value )
{
  if ( m__StructAddress.m__Country == value ) return;

  m__StructAddress.m__Country = value;
  emit changedCountry( value );
}

void Address::setSubject( Subject *value )
{
  if ( m__StructAddress.m__Subject == value ) return;

  m__StructAddress.m__Subject = value;
  emit changedSubject( value );
}

void Address::setRegion( Region *value )
{
  if ( m__StructAddress.m__Region == value ) return;

  m__StructAddress.m__Region = value;
  emit changedRegion( value );
}

void Address::setArea( Area *value )
{
  if ( m__StructAddress.m__Area == value ) return;

  m__StructAddress.m__Area = value;
  emit changedArea( value );
}

void Address::setCity( City *value )
{
  if ( m__StructAddress.m__City == value ) return;

  m__StructAddress.m__City = value;
  emit changedCity( value );
}

void Address::setInnerCity( InnerCity *value )
{
  if ( m__StructAddress.m__InnerCity == value ) return;

  m__StructAddress.m__InnerCity = value;
  emit changedInnerCity( value );
}

void Address::setTownship( Township *value )
{
  if ( m__StructAddress.m__Township == value ) return;

  m__StructAddress.m__Township = value;
  emit changedTownship( value );
}

void Address::setStreet( Street *value )
{
  if ( m__StructAddress.m__Street == value ) return;

  m__StructAddress.m__Street = value;
  emit changedStreet( value );
}

void Address::setSubaddress( Subaddress *value )
{
  if ( m__StructAddress.m__Subaddress == value ) return;

  m__StructAddress.m__Subaddress = value;
  emit changedSubaddress( value );
}

void Address::setSlaveaddress( AbstractSimpleObject *value )
{
  if ( m__StructAddress.m__Slaveaddress == value ) return;

  m__StructAddress.m__Slaveaddress = value;
  emit changedSlaveaddress( value );
}

void Address::setPostcode( AbstractSimpleObject *value )
{
  if ( m__StructAddress.m__Postcode == value ) return;

  m__StructAddress.m__Postcode = value;
  emit changedPostcode( value );
}

