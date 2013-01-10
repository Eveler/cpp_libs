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
  if ( m__StructSubaddress.m__Postcode == value ) return;

  m__StructSubaddress.m__Postcode = value;
  emit changedPostcode( value );
}

void Subaddress::setHouseNumber( QString value )
{
  if ( m__StructSubaddress.m__HouseNumber == value ) return;

  m__StructSubaddress.m__HouseNumber = value;
  emit changedHouseNumber( value );
}

void Subaddress::setBuildNumber( QString value )
{
  if ( m__StructSubaddress.m__BuildNumber == value ) return;

  m__StructSubaddress.m__BuildNumber = value;
  emit changedBuildNumber( value );
}

void Subaddress::setStructNumber( QString value )
{
  if ( m__StructSubaddress.m__StructNumber == value ) return;

  m__StructSubaddress.m__StructNumber = value;
  emit changedStructNumber( value );
}

void Subaddress::setStructureStatus( StructureStatus *value )
{
  if ( m__StructSubaddress.m__StructureStatus == value ) return;

  m__StructSubaddress.m__StructureStatus = value;
  emit changedStructureStatus( value );
}

