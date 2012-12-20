#include "subject.h"

Subject::Subject(QObject *parent) :
    QObject(parent)
{
  m__StructSubject.m__Id = QVariant();
  m__StructSubject.m__Abbreviation = NULL;
  m__StructSubject.m__Name = QString();
}

const QVariant & Subject::id() const
{
  return m__StructSubject.m__Id;
}

Abbreviation * Subject::abbreviation() const
{
  return m__StructSubject.m__Abbreviation;
}

const QString & Subject::name() const
{
  return m__StructSubject.m__Name;
}

void Subject::setId( QVariant value )
{
  m__StructSubject.m__Id = value;
}

void Subject::setAbbreviation( Abbreviation *value )
{
  if ( m__StructSubject.m__Abbreviation == value ) return;

  m__StructSubject.m__Abbreviation = value;
  emit changedAbbreviation( value );
}

void Subject::setName( QString value )
{
  if ( m__StructSubject.m__Name == value ) return;

  m__StructSubject.m__Name = value;
  emit changedName( value );
}

