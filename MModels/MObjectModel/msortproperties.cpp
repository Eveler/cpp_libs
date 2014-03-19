#include "msortproperties.h"

#include "mobjectmodel.h"


MSortProperties::MSortProperties(QQuickItem *parent) :
  QQuickItem(parent)
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

MSortProperties * MSortProperties::addSort( QString propertyName )
{
  MSortProperties *result = NULL;
  if ( m__SortProperties.contains( propertyName ) || propertyName.isEmpty() ) return result;

  result = new MSortProperties;
  m__SortProperties << propertyName;
  m__SortOrder << QVariant::fromValue( result );

  emit countChanged();
  return result;
}

MSortProperties * MSortProperties::replaceSort( int index, QString propertyName )
{
  MSortProperties *result = NULL;
  if ( index < 0 || index >= m__SortProperties.count() || propertyName.isEmpty() ) return result;

  result = new MSortProperties;
  m__SortProperties.replace( index, propertyName );
  m__SortOrder.replace( index, QVariant::fromValue( result ) );

  emit countChanged();
  return result;
}

void MSortProperties::removeSort( int index )
{
  if ( index < 0 || index >= m__SortProperties.count() ) return;

  m__SortProperties.removeAt( index );
  m__SortOrder.removeAt( index );

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

int MSortProperties::count() const
{
  return m__SortProperties.count();
}
