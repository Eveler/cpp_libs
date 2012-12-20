#include "street.h"

Street::Street(QObject *parent) :
    QObject(parent)
{
  m__StructStreet.m__Id = QVariant();
  m__StructStreet.m__Abbreviation = NULL;
  m__StructStreet.m__Name = QString();
}

const QVariant & Street::id() const
{
  return m__StructStreet.m__Id;
}

Abbreviation * Street::abbreviation() const
{
  return m__StructStreet.m__Abbreviation;
}

const QString & Street::name() const
{
  return m__StructStreet.m__Name;
}

void Street::setId( QVariant value )
{
  m__StructStreet.m__Id = value;
}

void Street::setAbbreviation( Abbreviation *value )
{
  if ( m__StructStreet.m__Abbreviation == value ) return;

  m__StructStreet.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void Street::setName( QString value )
{
  if ( m__StructStreet.m__Name == value ) return;

  m__StructStreet.m__Name = value;
  emit changedName( value );
}

