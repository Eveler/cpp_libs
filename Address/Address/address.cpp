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
  return m__StructAddress.m__Postalcode;
}

void Address::setId( QVariant value )
{
  m__StructAddress.m__Id = value;
}

void Address::setCountry( AbstractSimpleObject *value )
{
  m__StructAddress.m__Country = value;
}

void Address::setSubject( Subject *value )
{
  m__StructAddress.m__Subject = value;
}

void Address::setRegion( Region *value )
{
  m__StructAddress.m__Region = value;
}

void Address::setArea( Area *value )
{
  m__StructAddress.m__Area = value;
}

void Address::setCity( City *value )
{
  m__StructAddress.m__City = value;
}

void Address::setInnerCity( InnerCity *value )
{
  m__StructAddress.m__InnerCity = value;
}

void Address::setTownship( Township *value )
{
  m__StructAddress.m__Township = value;
}

void Address::setStreet( Street *value )
{
  m__StructAddress.m__Street = value;
}

void Address::setSubaddress( Subaddress *value )
{
  m__StructAddress.m__Subaddress = value;
}

void Address::setSlaveAddress( AbstractSimpleObject *value )
{
  m__StructAddress.m__Slaveaddress = value;
}

void Address::setPostalcode( AbstractSimpleObject *value )
{
  m__StructAddress.m__Postalcode = value;
}

