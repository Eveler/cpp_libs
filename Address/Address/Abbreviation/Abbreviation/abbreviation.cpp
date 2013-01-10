#include "abbreviation.h"

Abbreviation::Abbreviation(QObject *parent) :
    QObject(parent)
{
  m__StructAbbreviation.m__Id = QVariant();
  m__StructAbbreviation.m__ShortName = QString();
  m__StructAbbreviation.m__FullName = QString();
}

const QVariant & Abbreviation::id() const
{
  return m__StructAbbreviation.m__Id;
}

const QString & Abbreviation::shortName() const
{
  return m__StructAbbreviation.m__ShortName;
}

const QString & Abbreviation::fullName() const
{
  return m__StructAbbreviation.m__FullName;
}

void Abbreviation::setId( QVariant value )
{
  m__StructAbbreviation.m__Id = value;
}

void Abbreviation::setShortName( QString value )
{
  if ( m__StructAbbreviation.m__ShortName == value ) return;

  m__StructAbbreviation.m__ShortName = value;
  emit changedShortName( value );
}

void Abbreviation::setFullName( QString value )
{
  if ( m__StructAbbreviation.m__FullName == value ) return;

  m__StructAbbreviation.m__FullName = value;
  emit changedFullName( value );
}

