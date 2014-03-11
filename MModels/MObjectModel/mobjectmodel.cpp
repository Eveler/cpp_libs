#include "mobjectmodel.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ SafelyValue ]*
*/
SafelyValue::SafelyValue( QObject *value ) : QObject(value) {}

SafelyValue::~SafelyValue()
{
//  qDebug() << __func__;
}

QVariant SafelyValue::value() const
{
  QObject *object = parent();
  return QVariant::fromValue( object );
}
/*
 * End class definition: *[ SafelyValue ]*
*/


/*
 * Begin C++ - QML class definition: *[ MObjectModel ]*
*/
MObjectModel::MObjectModel( QObject * parent ) :
  QAbstractListModel(parent)
{
  connect( this, SIGNAL(modelReset()), SIGNAL(countChanged()) );
  connect( this, SIGNAL(rowsInserted(QModelIndex,int,int)), SIGNAL(countChanged()) );
  connect( this, SIGNAL(rowsRemoved(QModelIndex,int,int)), SIGNAL(countChanged()) );
}

MObjectModel::~MObjectModel()
{
  while ( !m__Objects.isEmpty() )
  {
    QObject *object = m__Objects.takeFirst();
    delete object;
    object = NULL;
  }
}

int MObjectModel::rowCount( const QModelIndex &index ) const
{
  Q_UNUSED(index)
  return m__Objects.count();
}

QVariant MObjectModel::data( const QModelIndex &index, int role ) const
{
  Q_UNUSED(role)
  if ( !index.isValid() || index.row() < 0 || index.row() >= m__Objects.count() ) return QVariant();

  return QVariant::fromValue( m__Objects[index.row()] );
}

SafelyValue * MObjectModel::get( int index ) const
{
  if ( index < 0 || index >= m__Objects.count() ) return NULL;

  SafelyValue *result = new SafelyValue( m__Objects[index] );
  result->deleteLater();
  return result;
}

void MObjectModel::append( QObject *object )
{
  if ( m__Objects.contains( object ) ) return;

  int index = m__Objects.count();
  beginInsertRows( QModelIndex(), index, index );
  m__Objects << object;
  endInsertRows();

//  emit countChanged();
}

void MObjectModel::insert( int index, QObject *object )
{
  if ( m__Objects.contains( object ) || index < 0 || index > m__Objects.count() ) return;

  beginInsertRows( QModelIndex(), index, index );
  m__Objects.insert( index, object );
  endInsertRows();

//  emit countChanged();
}

void MObjectModel::remove( int index )
{
  if ( index < 0 || index >= m__Objects.count() ) return;

  beginRemoveRows( QModelIndex(), index, index );
  m__Objects.removeAt( index );
  endRemoveRows();

//  emit countChanged();
}

void MObjectModel::replace( int index, QObject *object )
{
  if ( index < 0 || index >= m__Objects.count() ) return;

  m__Objects.replace( index, object );

  QVector<int> roles;
  roles << (int)ObjectRole;
  emit dataChanged( createIndex( index, 0 ), createIndex( index, 0 ), roles );
}

int MObjectModel::index( QObject *object ) const
{
  return m__Objects.indexOf( object );
}

int MObjectModel::count() const
{
  return m__Objects.count();
}

QHash<int, QByteArray> MObjectModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[ObjectRole] = "object";

  return roles;
}
/*
 * End class definition: *[ MObjectModel ]*
*/

