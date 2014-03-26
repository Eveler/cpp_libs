#include "msortproperties.h"

#include "mobjectmodel.h"


MSortProperties::MSortProperties( QObject *parent ) :
  QObject(parent)
{
}

MSortProperties::~MSortProperties()
{
  m__SortProperties.clear();
  while ( !m__SortOrder.isEmpty() )
  {
    QVariant sortOrder = m__SortOrder.takeFirst();
    if ( sortOrder.type() == (int)QMetaType::QObjectStar )
    {
      MSortProperties *sort = sortOrder.value<MSortProperties *>();
      sortOrder.clear();
      delete sort;
      sort = NULL;
    }
  }
}

void MSortProperties::addSort( QString propertyName, Qt::SortOrder order )
{
  if ( m__SortProperties.contains( propertyName ) || propertyName.isEmpty() ) return;

  m__SortProperties << propertyName;
  m__SortOrder << QVariant( order );

  emit countChanged();
}

void MSortProperties::replaceSort( int index, QString propertyName, Qt::SortOrder order )
{
  if ( index < 0 || index >= m__SortProperties.count() || propertyName.isEmpty() ) return;

  m__SortProperties.replace( index, propertyName );
  m__SortOrder.replace( index, QVariant( order ) );

  emit countChanged();
}

SafelyValue * MSortProperties::addSort( QString propertyName )
{
  if ( m__SortProperties.contains( propertyName ) || propertyName.isEmpty() ) return NULL;

  MSortProperties *result = new MSortProperties;
  m__SortProperties << propertyName;
  m__SortOrder << QVariant::fromValue( result );

  emit countChanged();
  SafelyValue *safelyValue = new SafelyValue( QVariant::fromValue( result ) );
  safelyValue->deleteLater();
  return safelyValue;
}

SafelyValue * MSortProperties::replaceSort( int index, QString propertyName )
{
  if ( index < 0 || index >= m__SortProperties.count() || propertyName.isEmpty() ) return NULL;

  MSortProperties *result = new MSortProperties;
  m__SortProperties.replace( index, propertyName );
  QVariant sortOrder = m__SortOrder.at( index );
  m__SortOrder.replace( index, QVariant::fromValue( result ) );
  if ( sortOrder.canConvert<MSortProperties *>() )
  {
    MSortProperties *sort = sortOrder.value<MSortProperties *>();
    sortOrder.clear();
    delete sort;
    sort = NULL;
  }

  emit countChanged();
  SafelyValue *safelyValue = new SafelyValue( QVariant::fromValue( result ) );
  safelyValue->deleteLater();
  return safelyValue;
}

void MSortProperties::removeSort( int index )
{
  if ( index < 0 || index >= m__SortProperties.count() ) return;

  m__SortProperties.removeAt( index );
  QVariant sortOrder = m__SortOrder.takeAt( index );
  if ( sortOrder.canConvert<MSortProperties *>() )
  {
    MSortProperties *sort = sortOrder.value<MSortProperties *>();
    sortOrder.clear();
    delete sort;
    sort = NULL;
  }

  emit countChanged();
}

QString MSortProperties::sortProperty( int index ) const
{
  return m__SortProperties.value( index, QString() );
}

SafelyValue * MSortProperties::sortOrder( int index ) const
{
  if ( index < 0 || index >= m__SortProperties.count() ) return NULL;

  SafelyValue *result = new SafelyValue( m__SortOrder[index] );
  result->deleteLater();
  return result;
}

void MSortProperties::clear()
{
  while ( !m__SortProperties.isEmpty() )
  {
    m__SortProperties.removeFirst();
    QVariant sortOrder = m__SortOrder.takeFirst();
    if ( sortOrder.canConvert<MSortProperties *>() )
    {
      MSortProperties *sort = sortOrder.value<MSortProperties *>();
      sortOrder.clear();
      delete sort;
      sort = NULL;
    }
  }

  emit countChanged();
}

int MSortProperties::count() const
{
  return m__SortProperties.count();
}
