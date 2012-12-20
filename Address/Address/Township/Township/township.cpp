#include "township.h"

Township::Township(QObject *parent) :
    QObject(parent)
{
  m__StructTownship.m__Id = QVariant();
  m__StructTownship.m__Abbreviation = NULL;
  m__StructTownship.m__Name = QString();
}

const QVariant & Township::id() const
{
  return m__StructTownship.m__Id;
}

Abbreviation * Township::abbreviation() const
{
  return m__StructTownship.m__Abbreviation;
}

const QString & Township::name() const
{
  return m__StructTownship.m__Name;
}

void Township::setId( QVariant value )
{
  m__StructTownship.m__Id = value;
}

void Township::setAbbreviation( Abbreviation *value )
{
  m__StructTownship.m__Abbreviation = value;
}

void Township::setName( QString value )
{
  m__StructTownship.m__Name = value;
}

