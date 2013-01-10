#include "city.h"

City::City(QObject *parent) :
    QObject(parent)
{
  m__StructCity.m__Id = QVariant();
  m__StructCity.m__Abbreviation = NULL;
  m__StructCity.m__Name = QString();
}

const QVariant & City::id() const
{
  return m__StructCity.m__Id;
}

Abbreviation * City::abbreviation() const
{
  return m__StructCity.m__Abbreviation;
}

const QString & City::name() const
{
  return m__StructCity.m__Name;
}

void City::setId( QVariant value )
{
  m__StructCity.m__Id = value;
}

void City::setAbbreviation( Abbreviation *value )
{
  if ( m__StructCity.m__Abbreviation == value ) return;

  m__StructCity.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void City::setName( QString value )
{
  if ( m__StructCity.m__Name == value ) return;

  m__StructCity.m__Name = value;
  emit changedName( value );
}

