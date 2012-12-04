#include "notification.h"

Notification::Notification(QObject *parent) :
    QObject(parent)
{
  clear();
}

Notification::~Notification()
{
  clear();
}

const QVariant & Notification::id() const
{
  return m__Value.m__Id;
}

QDateTime Notification::created() const
{
  return m__Value.m__Created;
}

User * Notification::creator() const
{
  return m__Value.m__Creator;
}
void Notification::clear()
{
  setId( QVariant() );
  setCreated( QDateTime() );
  setCreator( NULL );
}

void Notification::setId( QVariant value )
{
  m__Value.m__Id = value;
}

void Notification::setCreated( QDateTime value )
{
  m__Value.m__Created = value;
}

void Notification::setCreator( User *value )
{
  m__Value.m__Creator = value;
}

