#include "innercity.h"

InnerCity::InnerCity(QObject *parent) :
    QObject(parent)
{
  m__StructInnerCity.m__Id = QVariant();
  m__StructInnerCity.m__Abbreviation = NULL;
  m__StructInnerCity.m__Name = QString();
}

const QVariant & InnerCity::id() const
{
  return m__StructInnerCity.m__Id;
}

Abbreviation * InnerCity::abbreviation() const
{
  return m__StructInnerCity.m__Abbreviation;
}

const QString & InnerCity::name() const
{
  return m__StructInnerCity.m__Name;
}

void InnerCity::setId( QVariant value )
{
  m__StructInnerCity.m__Id = value;
}

void InnerCity::setAbbreviation( Abbreviation *value )
{
  if ( m__StructInnerCity.m__Abbreviation == value ) return;

  m__StructInnerCity.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void InnerCity::setName( QString value )
{
  if ( m__StructInnerCity.m__Name == value ) return;

  m__StructInnerCity.m__Name = value;
  emit changedName( value );
}

