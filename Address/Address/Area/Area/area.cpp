#include "area.h"

Area::Area(QObject *parent) :
    QObject(parent)
{
  m__StructArea.m__Id = QVariant();
  m__StructArea.m__Abbreviation = NULL;
  m__StructArea.m__Name = QString();
}

const QVariant & Area::id() const
{
  return m__StructArea.m__Id;
}

Abbreviation * Area::abbreviation() const
{
  return m__StructArea.m__Abbreviation;
}

const QString & Area::name() const
{
  return m__StructArea.m__Name;
}

void Area::setId( QVariant value )
{
  m__StructArea.m__Id = value;
}

void Area::setAbbreviation( Abbreviation *value )
{
  if ( m__StructArea.m__Abbreviation == value ) return;

  m__StructArea.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void Area::setName( QString value )
{
  if ( m__StructArea.m__Name == value ) return;

  m__StructArea.m__Name = value;
  emit changedName( value );
}

