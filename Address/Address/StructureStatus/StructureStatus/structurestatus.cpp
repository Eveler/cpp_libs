#include "structurestatus.h"

StructureStatus::StructureStatus(QObject *parent) :
    QObject(parent)
{
  m__StructStructureStatus.m__Id = QVariant();
  m__StructStructureStatus.m__ShortName = QString();
  m__StructStructureStatus.m__FullName = QString();
}

const QVariant & StructureStatus::id() const
{
  return m__StructStructureStatus.m__Id;
}

const QString & StructureStatus::shortName() const
{
  return m__StructStructureStatus.m__ShortName;
}

const QString & StructureStatus::fullName() const
{
  return m__StructStructureStatus.m__FullName;
}

void StructureStatus::setId( QVariant value )
{
  m__StructStructureStatus.m__Id = value;
}

void StructureStatus::setShortName( QString value )
{
  if ( m__StructStructureStatus.m__ShortName == value ) return;

  m__StructStructureStatus.m__ShortName = value;
  emit changedShortName( value );
}

void StructureStatus::setFullName( QString value )
{
  if ( m__StructStructureStatus.m__FullName == value ) return;

  m__StructStructureStatus.m__FullName = value;
  emit changedFullName( value );
}

