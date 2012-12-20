#include "subaddress.h"

Subaddress::Subaddress(QObject *parent) :
    QObject(parent)
{
  m__StructSubaddress.m__Id = QVariant();
  m__StructSubaddress.m__Postcode = NULL;
  m__StructSubaddress.m__HouseNumber = QString();
  m__StructSubaddress.m__BuildNumber = QString();
  m__StructSubaddress.m__StructNumber = QString();
  m__StructSubaddress.m__StructureStatus = NULL;
}

const QVariant & Subaddress::id() const
{
  return m__StructSubaddress.m__Id;
}

AbstractSimpleObject * Subaddress::postcode() const
{
  return m__StructSubaddress.m__Postcode;
}

const QString & Subaddress::houseNumber() const
{
  return m__StructSubaddress.m__HouseNumber;
}

const QString & Subaddress::buildNumber() const
{
  return m__StructSubaddress.m__BuildNumber;
}

const QString & Subaddress::structNumber() const
{
  return m__StructSubaddress.m__StructNumber;
}

StructureStatus * Subaddress::structureStatus() const
{
  return m__StructSubaddress.m__StructureStatus;
}

void Subaddress::setId( QVariant value )
{
  m__StructSubaddress.m__Id = value;
}

void Subaddress::setPostcode( AbstractSimpleObject *value )
{
  m__StructSubaddress.m__Postcode = value;
}

void Subaddress::setHouseNumber( QString value )
{
  m__StructSubaddress.m__HouseNumber = value;
}

void Subaddress::setBuildNumber( QString value )
{
  m__StructSubaddress.m__BuildNumber = value;
}

void Subaddress::setStructNumber( QString value )
{
  m__StructSubaddress.m__StructNumber = value;
}

void Subaddress::setStructureStatus( StructureStatus *value )
{
  m__StructSubaddress.m__StructureStatus = value;
}

