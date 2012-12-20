#include "region.h"

Region::Region(QObject *parent) :
    QObject(parent)
{
  m__StructRegion.m__Id = QVariant();
  m__StructRegion.m__Abbreviation = NULL;
  m__StructRegion.m__Name = QString();
}

const QVariant & Region::id() const
{
  return m__StructRegion.m__Id;
}

Abbreviation * Region::abbreviation() const
{
  return m__StructRegion.m__Abbreviation;
}

const QString & Region::name() const
{
  return m__StructRegion.m__Name;
}

void Region::setId( QVariant value )
{
  m__StructRegion.m__Id = value;
}

void Region::setAbbreviation( Abbreviation *value )
{
  if ( m__StructRegion.m__Abbreviation == value ) return;

  m__StructRegion.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void Region::setName( QString value )
{
  if ( m__StructRegion.m__Name == value ) return;

  m__StructRegion.m__Name = value;
  emit changedName( value );
}

