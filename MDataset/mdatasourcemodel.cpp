#include "mdatasourcemodel.h"


/*
 * Begin C++ class definition: *[ ObjectListPrivate ]*
*/
ObjectListPrivate::ObjectListPrivate() {}

ObjectListPrivate::~ObjectListPrivate()
{
  while( !m__Objects.isEmpty() )
    m__Objects.take( m__Objects.keys().first() ).clear();
  while( !m__StarObjects.isEmpty() )
    m__StarObjects.take( m__StarObjects.keys().first() ).clear();
}

QVariantList ObjectListPrivate::sourceTypes() const
{
  QVariantList result;

  foreach ( int sourceType, m__Objects.keys() )
    result << QVariant( sourceType );
  foreach ( QObject *sourceType, m__StarObjects.keys() )
    result << QVariant::fromValue( sourceType );

  return result;
}

QObject * ObjectListPrivate::pObject( int sourceType, int index ) const
{
  return m__Objects.value( sourceType, QObjectList() ).value( index, NULL );
}

int ObjectListPrivate::pCount( int sourceType ) const
{
  return m__Objects.value( sourceType, QObjectList() ).count();
}

int ObjectListPrivate::pIndex( int sourceType, QObject *object ) const
{
  return m__Objects.value( sourceType, QObjectList() ).indexOf( object );
}

void ObjectListPrivate::pInsert( int sourceType, QObject *object, int index )
{
  if ( !m__Objects.contains( sourceType ) ) m__Objects[sourceType] = QObjectList();

  if ( index < 0 || index >= m__Objects[sourceType].count() ) m__Objects[sourceType] << object;
  else m__Objects[sourceType].insert( index, object );
}

QObject * ObjectListPrivate::pTake( int sourceType, int index )
{
  QObject *result = m__Objects[sourceType].takeAt( index );
  if ( m__Objects[sourceType].isEmpty() ) m__Objects.remove( sourceType );
  return result;
}

QObject * ObjectListPrivate::pObject( QObject * sourceType, int index ) const
{
  return m__StarObjects.value( sourceType, QObjectList() ).value( index, NULL );
}

int ObjectListPrivate::pCount( QObject *sourceType ) const
{
  return m__StarObjects.value( sourceType, QObjectList() ).count();
}

int ObjectListPrivate::pIndex( QObject *sourceType, QObject *object ) const
{
  return m__StarObjects.value( sourceType, QObjectList() ).indexOf( object );
}

void ObjectListPrivate::pInsert( QObject *sourceType, QObject *object, int index )
{
  if ( !m__StarObjects.contains( sourceType ) ) m__StarObjects[sourceType] = QObjectList();

  if ( index < 0 || index >= m__StarObjects[sourceType].count() ) m__StarObjects[sourceType] << object;
  else m__StarObjects[sourceType].insert( index, object );
}

QObject * ObjectListPrivate::pTake( QObject *sourceType, int index )
{
  QObject *result = m__StarObjects[sourceType].takeAt( index );
  if ( m__StarObjects[sourceType].isEmpty() ) m__StarObjects.remove( sourceType );
  return result;
}
/*
 * End class definition: *[ ObjectListPrivate ]*
*/


/*
 * Begin C++ - QML class definition: *[ MDataSourceModel ]*
*/
MDataSourceModel::MDataSourceModel(QObject *parent) :
  MObjectModel(parent),
  m__Source(NULL),
  m__SourceType(-1)
{
}

MDataSourceModel::~MDataSourceModel()
{
  m__Source = NULL;
}

int MDataSourceModel::rowCount( const QModelIndex &index ) const
{
  Q_UNUSED(index)

  int result = 0;
  if ( m__Source == NULL ) return result;

  if ( m__SourceType == -1 ) result = m__Source->count( (MDataSourceModel *)this );
  else result = m__Source->count( m__SourceType );

  return result;
}

QVariant MDataSourceModel::data( const QModelIndex &index, int role ) const
{
  Q_UNUSED(role)
  if ( m__Source == NULL || !index.isValid() || index.row() < 0 ) return QVariant();

  QObject *object = NULL;

  if ( m__SourceType == -1 )
  {
    if ( index.row() >= m__Source->count( (MDataSourceModel *)this ) ) return QVariant();

    object = m__Source->object( (MDataSourceModel *)this, index.row() );
  }
  else
  {
    if ( index.row() >= m__Source->count( m__SourceType ) ) return QVariant();

    object = m__Source->object( m__SourceType, index.row() );
  }

  return QVariant::fromValue( object );
}

SafelyValue * MDataSourceModel::get( int index ) const
{
  if ( m__Source == NULL || index < 0 )
  {
    qDebug() << __func__ << index;
    return NULL;
  }

  SafelyValue *result = NULL;
  if ( m__SourceType == -1 )
  {
    if ( index >= m__Source->count( (MDataSourceModel *)this ) )
    {
      qDebug() << __func__ << index;
      return NULL;
    }

    result = new SafelyValue( QVariant::fromValue( m__Source->object( (MDataSourceModel *)this, index ) ) );
  }
  else
  {
    if ( index >= m__Source->count( m__SourceType ) )
    {
      qDebug() << __func__ << index;
      return NULL;
    }

    result = new SafelyValue( QVariant::fromValue(  m__Source->object( m__SourceType, index ) ) );
  }

  result->deleteLater();
  return result;
}

void MDataSourceModel::append( QObject *object )
{
  Q_UNUSED(object)
}

void MDataSourceModel::insert( int index, QObject *object )
{
  Q_UNUSED(index)
  Q_UNUSED(object)
}

void MDataSourceModel::remove( int index )
{
  Q_UNUSED(index)
}

void MDataSourceModel::replace( int index, QObject *object )
{
  Q_UNUSED(index)
  Q_UNUSED(object)
}

int MDataSourceModel::index( QObject *object ) const
{
  if ( m__Source == NULL ) return -1;

  if ( m__SourceType == -1 ) return m__Source->index( (MDataSourceModel *)this, object );
  else return m__Source->index( m__SourceType, object );
}

int MDataSourceModel::count() const
{
  int result = 0;
  if ( m__Source == NULL ) return result;

  if ( m__SourceType == -1 ) result = m__Source->count( (MDataSourceModel *)this );
  else result = m__Source->count( m__SourceType );

  return result;
}

void MDataSourceModel::clear() {}

void MDataSourceModel::setSource( ObjectListPrivate *source )
{
  if ( m__Source == source ) return;

  m__Source = source;
  resetModel();
}

int MDataSourceModel::sourceType() const
{
  return m__SourceType;
}

void MDataSourceModel::setSourceType( int sourceType )
{
  m__SourceType = sourceType;
  emit sourceTypeChanged();
}

void MDataSourceModel::resetModel()
{
  beginResetModel();
  endResetModel();
}

void MDataSourceModel::insertObjects( int first, int last )
{
  beginInsertRows( QModelIndex(), first, last );
  endInsertRows();
}

void MDataSourceModel::removeObjects( int first, int last )
{
  beginRemoveRows( QModelIndex(), first, last );
  endRemoveRows();
}
/*
 * End class definition: *[ MDataSourceModel ]*
*/
