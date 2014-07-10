#include "mobjectmodel.h"

#include <QDebug>


/*
 * Begin C++ - QML class definition: *[ SafelyValue ]*
*/
SafelyValue::SafelyValue( const QVariant &value ) :
  QObject(NULL),
  m__Value(value)
{}

SafelyValue::~SafelyValue()
{
//  qDebug() << __func__;
}

QVariant SafelyValue::value() const
{
  return m__Value;
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

  SafelyValue *result = new SafelyValue( QVariant::fromValue( m__Objects[index] ) );
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
}

void MObjectModel::insert( int index, QObject *object )
{
  if ( m__Objects.contains( object ) || index < 0 || index > m__Objects.count() ) return;

  beginInsertRows( QModelIndex(), index, index );
  m__Objects.insert( index, object );
  endInsertRows();
}

void MObjectModel::remove( int index )
{
  if ( index < 0 || index >= m__Objects.count() ) return;

  beginRemoveRows( QModelIndex(), index, index );
  m__Objects.removeAt( index );
  endRemoveRows();
}

void MObjectModel::replace( int index, QObject *object )
{
  if ( index < 0 || index >= m__Objects.count() ) return;

  m__Objects.replace( index, object );

  QVector<int> roles = QVector<int>::fromList( roleNames().keys() );
  emit dataChanged( createIndex( index, 0 ), createIndex( index, 0 ), roles );
}

void MObjectModel::move( int fromIndex, int toIndex, int count )
{
  if ( fromIndex == toIndex || fromIndex+count > m__Objects.count() || toIndex+count > m__Objects.count() || fromIndex < 0 || toIndex < 0 || count < 0 ) return;

  beginMoveRows( QModelIndex(), fromIndex, fromIndex+count-1, QModelIndex(), ( toIndex > fromIndex ? toIndex+count : toIndex ) );
  if ( fromIndex > toIndex )
  {
    QList<QObject *> arr_BeforeTo = m__Objects.mid( 0, toIndex );
    QList<QObject *> arr_Moved = m__Objects.mid( fromIndex, count );
    QList<QObject *> arr_MidToFrom = m__Objects.mid( toIndex, fromIndex-toIndex );
    QList<QObject *> arr_AfterFrom = m__Objects.mid( fromIndex+count );
    m__Objects.clear();
    m__Objects << arr_BeforeTo;
    m__Objects << arr_Moved;
    m__Objects << arr_MidToFrom;
    m__Objects << arr_AfterFrom;
  }
  else
  {
    QList<QObject *> arr_BeforeFrom = m__Objects.mid( 0, fromIndex );
    QList<QObject *> arr_Moved = m__Objects.mid( fromIndex, count );
    QList<QObject *> arr_MidFromTo = m__Objects.mid( fromIndex+count, toIndex-fromIndex );
    QList<QObject *> arr_AfterTo = m__Objects.mid( toIndex+count );
    m__Objects.clear();
    m__Objects << arr_BeforeFrom;
    m__Objects << arr_MidFromTo;
    m__Objects << arr_Moved;
    m__Objects << arr_AfterTo;
  }
  endMoveRows();
}

int MObjectModel::index( QObject *object ) const
{
  return m__Objects.indexOf( object );
}

int MObjectModel::count() const
{
  return m__Objects.count();
}

void MObjectModel::clear()
{
  beginResetModel();
  m__Objects.clear();
  endResetModel();
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

