#include "mcalculationalmodel.h"

#include "mcalculationalmodelprivate.h"
#include "mcalculationalrow.h"


MCalculationalModel::MCalculationalModel(QObject *parent) :
  QAbstractItemModel(parent)
{
  declareValues();
}

int MCalculationalModel::rowCount( const QModelIndex &/*parent*/ ) const
{
  return p->m__Rows.count();
}

int MCalculationalModel::columnCount( const QModelIndex &/*parent*/ ) const
{
  return p->m__Header.count();
}

QModelIndex MCalculationalModel::index( int row, int column, const QModelIndex &/*parent*/ ) const
{
  if ( row < 0 || row >= p->m__Rows.count() ||
       column < 0 || column >= p->m__Header.count() )
    return QModelIndex();

  return QAbstractItemModel::createIndex( row, column );
}

QVariant MCalculationalModel::data( const QModelIndex &index, int role ) const
{
//  if ( index.row() < 0 || index.row() >= p->m__Data.count() ||
//       index.column() < 0 || index.column() >= p->m__Header.count() )
//    return QVariant();
  if ( !index.isValid() || role != Qt::DisplayRole ) return QVariant();
  if ( !QAbstractItemModel::hasIndex( index.row(), index.column(), index.parent() ) )
    return QVariant();

  return p->m__Rows[index.row()]->data( index.column() );
}

QVariant MCalculationalModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
  if ( role != Qt::DisplayRole ) return QVariant();

  if ( orientation == Qt::Horizontal )
  {
    if ( section < 0 || section >= p->m__Header.count() )
      return QVariant();

    return p->m__Header[section];
  }
  else
  {
    if ( section < 0 || section >= p->m__Rows.count() )
      return QVariant();

    return (section+1);
  }
}

QModelIndex MCalculationalModel::parent( const QModelIndex &/*child*/ ) const
{
  return QModelIndex();
}

bool MCalculationalModel::insertRow( int row, const QModelIndex &parent )
{
  if ( row < 0 || row > p->m__Rows.count() ) return false;

  QAbstractItemModel::beginInsertRows( parent, row, row );
  MCalculationalRow *rowData = new MCalculationalRow( this );
  p->m__Rows.insert( row, rowData );
  rowData = NULL;
  QAbstractItemModel::endInsertRows();

  return true;
}

bool MCalculationalModel::insertRows( int row, int count, const QModelIndex &parent )
{
  if ( row < 0 || row > p->m__Rows.count() || count < 1 ) return false;

  QAbstractItemModel::beginInsertRows( parent, row, row+count-1 );
  int inserted = 0;
  while ( inserted < count )
  {
    MCalculationalRow *rowData = new MCalculationalRow( this );
    p->m__Rows.insert( row, rowData );
    rowData = NULL;
    inserted++;
  }
  QAbstractItemModel::endInsertRows();

  return true;
}

bool MCalculationalModel::removeRow( int row, const QModelIndex &parent )
{
  if ( row < 0 || row >= p->m__Rows.count() ) return false;

  QAbstractItemModel::beginRemoveRows( parent, row, row );
  MCalculationalRow *rowData = p->m__Rows.takeAt( row );
  delete rowData;
  rowData = NULL;
  QAbstractItemModel::endRemoveRows();

  return true;
}

bool MCalculationalModel::removeRows( int row, int count, const QModelIndex &parent )
{
  if ( row < 0 || row >= p->m__Rows.count() || count < 1 ||
       (row+count-1) >= p->m__Rows.count() )
    return false;

  QAbstractItemModel::beginRemoveRows( parent, row, row+count-1 );
  int removed = 0;
  while ( removed < count )
  {
    MCalculationalRow *rowData = p->m__Rows.takeAt( row );
    delete rowData;
    rowData = NULL;
    removed++;
  }
  QAbstractItemModel::endRemoveRows();

  return true;
}

bool MCalculationalModel::insertColumn( int column, const QModelIndex &parent )
{
  if ( column < 0 || column > p->m__Header.count() ) return false;

  QAbstractItemModel::beginInsertColumns( parent, column, column );
  p->m__Header.insert( column, QVariant() );

  for ( int rIdx = 0; rIdx < p->m__Rows.count(); rIdx++ )
    p->m__Rows[rIdx]->insert( column );
  QAbstractItemModel::endInsertColumns();

  return true;
}

bool MCalculationalModel::insertColumns( int column, int count, const QModelIndex &parent )
{
  if ( column < 0 || column > p->m__Header.count() || count < 1 ) return false;

  QAbstractItemModel::beginInsertColumns( parent, column, column+count-1 );
  int inserted = 0;
  while ( inserted < count )
  {
    p->m__Header.insert( column, QVariant() );
    inserted++;
  }

  for ( int rIdx = 0; rIdx < p->m__Rows.count(); rIdx++ )
    while ( p->m__Rows[rIdx]->sectionCount() < p->m__Header.count() )
      p->m__Rows[rIdx]->insert( column );
  QAbstractItemModel::endInsertColumns();

  return true;
}

bool MCalculationalModel::removeColumn( int column, const QModelIndex &parent )
{
  if ( column < 0 || column >= p->m__Header.count() ) return false;

  QAbstractItemModel::beginRemoveColumns( parent, column, column );
  p->m__Header.removeAt( column );

  for ( int rIdx = 0; rIdx < p->m__Rows.count(); rIdx++ )
    p->m__Rows[rIdx]->remove( column );
  QAbstractItemModel::endRemoveColumns();

  return true;
}

bool MCalculationalModel::removeColumns( int column, int count, const QModelIndex &parent )
{
  if ( column < 0 || column >= p->m__Header.count() || count < 1 ||
       (column+count-1) >= p->m__Header.count() )
    return false;

  QAbstractItemModel::beginRemoveColumns( parent, column, column+count-1 );
  int removed = 0;
  while ( removed < count )
  {
    p->m__Header.removeAt( column );
    removed++;
  }

  for ( int rIdx = 0; rIdx < p->m__Rows.count(); rIdx++ )
    while ( p->m__Rows[rIdx]->sectionCount() > p->m__Header.count() )
      p->m__Rows[rIdx]->remove( column );
  QAbstractItemModel::endRemoveColumns();

  return true;
}

bool MCalculationalModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
  if ( !QAbstractItemModel::hasIndex( index.row(), index.column(), index.parent() ) )
    return false;
  if ( role != Qt::DisplayRole ) return false;

  p->m__Rows[index.row()]->setData( index.column(), value );

  emit dataChanged( index, index );

  return true;
}

bool MCalculationalModel::setHeaderData(
    int section, Qt::Orientation orientation, const QVariant &value, int role )
{
  if ( orientation != Qt::Horizontal || role != Qt::DisplayRole ) return false;

  if ( section < 0 || section >= p->m__Header.count() ) return false;

  p->m__Header[section] = value;

  emit headerDataChanged( orientation, section, section );

  return true;
}

MCalculationalRow * MCalculationalModel::row( int rowIndex ) const
{
  if ( rowIndex < 0 || rowIndex >= p->m__Rows.count() ) return NULL;

  return p->m__Rows[rowIndex];
}

int MCalculationalModel::findRow( MCalculationalRow *row ) const
{
  return p->m__Rows.indexOf( row );
}

void MCalculationalModel::declareValues()
{
  p = new MCalculationalModelPrivate( this );
}
