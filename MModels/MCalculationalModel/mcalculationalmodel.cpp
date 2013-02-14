#include "mcalculationalmodel.h"

#include "mcalculationalmodelprivate.h"
#include "mabstractrowcalculationalgorithm.h"
#include "mabstractcolumncalculationalgorithm.h"

#include <QCoreApplication>


MCalculationalModel::MCalculationalModel(QObject *parent) :
  QAbstractItemModel(parent)
{
  declareValues();
}

MCalculationalModel::~MCalculationalModel()
{
  while ( !p->m__Columns.isEmpty() )
  {
    MCalculationalColumn *column = p->m__Columns.takeFirst();
    connect( column, SIGNAL(labelChanged(QVariant,QVariant)),
             this, SLOT(columnLabelChanged(QVariant,QVariant)) );
    connect( column, SIGNAL(dataChanged(int,QVariant,QVariant)),
             this, SLOT(columnDataChanged(int,QVariant,QVariant)) );
    delete column;
    column = NULL;
  }
  while ( !p->m__Rows.isEmpty() )
  {
    MCalculationalRow *row = p->m__Rows.takeFirst();
    delete row;
    row = NULL;
  }
}

int MCalculationalModel::rowCount( const QModelIndex &/*parent*/ ) const
{
  return p->m__Rows.count();
}

int MCalculationalModel::columnCount( const QModelIndex &/*parent*/ ) const
{
  return p->m__Columns.count();
}

QModelIndex MCalculationalModel::index( int row, int column, const QModelIndex &/*parent*/ ) const
{
  if ( row < 0 || row >= p->m__Rows.count() ||
       column < 0 || column >= p->m__Columns.count() )
    return QModelIndex();

  return QAbstractItemModel::createIndex( row, column );
}

QVariant MCalculationalModel::data( const QModelIndex &index, int role ) const
{
  if ( !index.isValid() || role != Qt::DisplayRole ) return QVariant();
  if ( !QAbstractItemModel::hasIndex( index.row(), index.column(), index.parent() ) )
    return QVariant();

  return p->m__Columns[index.column()]->data( index.row() );
}

QVariant MCalculationalModel::headerData(
    int section, Qt::Orientation orientation, int role ) const
{
  if ( role != Qt::DisplayRole ) return QVariant();

  if ( orientation == Qt::Horizontal )
  {
    if ( section < 0 || section >= p->m__Columns.count() )
      return QVariant();

    return p->m__Columns[section]->label();
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
  foreach ( MCalculationalColumn *column, p->m__Columns )
    column->insert( row );
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
    foreach ( MCalculationalColumn *column, p->m__Columns )
      column->insert( row );
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
  foreach ( MCalculationalColumn *column, p->m__Columns )
    column->remove( row );
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
    foreach ( MCalculationalColumn *column, p->m__Columns )
      column->remove( row );
    removed++;
  }
  QAbstractItemModel::endRemoveRows();

  return true;
}

bool MCalculationalModel::insertColumn( int column, const QModelIndex &parent )
{
  if ( column < 0 || column > p->m__Columns.count() ) return false;

  QAbstractItemModel::beginInsertColumns( parent, column, column );
  MCalculationalColumn *columnData = new MCalculationalColumn( this );
  connect( columnData, SIGNAL(labelChanged(QVariant,QVariant)),
           SLOT(columnLabelChanged(QVariant,QVariant)) );
  connect( columnData, SIGNAL(dataChanged(int,QVariant,QVariant)),
           SLOT(columnDataChanged(int,QVariant,QVariant)) );
  p->m__Columns.insert( column, columnData );
  QAbstractItemModel::endInsertColumns();

  return true;
}

bool MCalculationalModel::insertColumns( int column, int count, const QModelIndex &parent )
{
  if ( column < 0 || column > p->m__Columns.count() || count < 1 ) return false;

  QAbstractItemModel::beginInsertColumns( parent, column, column+count-1 );
  int inserted = 0;
  while ( inserted < count )
  {
    MCalculationalColumn *columnData = new MCalculationalColumn( this );
    connect( columnData, SIGNAL(labelChanged(QVariant,QVariant)),
             SLOT(columnLabelChanged(QVariant,QVariant)) );
    connect( columnData, SIGNAL(dataChanged(int,QVariant,QVariant)),
             SLOT(columnDataChanged(int,QVariant,QVariant)) );
    p->m__Columns.insert( column, columnData );
    inserted++;
  }
  QAbstractItemModel::endInsertColumns();

  return true;
}

bool MCalculationalModel::removeColumn( int column, const QModelIndex &parent )
{
  if ( column < 0 || column >= p->m__Columns.count() ) return false;

  QAbstractItemModel::beginRemoveColumns( parent, column, column );
  MCalculationalColumn *columnData = p->m__Columns.takeAt( column );
  delete columnData;
  columnData = NULL;
  QAbstractItemModel::endRemoveColumns();

  return true;
}

bool MCalculationalModel::removeColumns( int column, int count, const QModelIndex &parent )
{
  if ( column < 0 || column >= p->m__Columns.count() || count < 1 ||
       (column+count-1) >= p->m__Columns.count() )
    return false;

  QAbstractItemModel::beginRemoveColumns( parent, column, column+count-1 );
  int removed = 0;
  while ( removed < count )
  {
    MCalculationalColumn *columnData = p->m__Columns.takeAt( column );
    delete columnData;
    columnData = NULL;
    removed++;
  }
  QAbstractItemModel::endRemoveColumns();

  return true;
}

bool MCalculationalModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
  if ( !QAbstractItemModel::hasIndex( index.row(), index.column(), index.parent() ) )
    return false;
  if ( role != Qt::DisplayRole ) return false;

  return p->m__Columns[index.column()]->setData( index.row(), value );
}

bool MCalculationalModel::setHeaderData(
    int section, Qt::Orientation orientation, const QVariant &value, int role )
{
  if ( orientation != Qt::Horizontal || role != Qt::DisplayRole ) return false;

  if ( section < 0 || section >= p->m__Columns.count() ) return false;

  p->m__Columns[section]->setLabel( value );

  return true;
}

Qt::ItemFlags MCalculationalModel::flags(const QModelIndex & index) const
{
  if ( !QAbstractItemModel::hasIndex( index.row(), index.column(), index.parent() ) )
    return Qt::NoItemFlags;

  return (Qt::ItemIsEnabled | Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/);
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

MCalculationalColumn * MCalculationalModel::column( int columnIndex ) const
{
  if ( columnIndex < 0 || columnIndex >= p->m__Columns.count() ) return NULL;

  return p->m__Columns[columnIndex];
}

int MCalculationalModel::findColumn( MCalculationalColumn *column ) const
{
  return p->m__Columns.indexOf( column );
}

void MCalculationalModel::calculate()
{
  do
  {
    while ( !p->m__PreparedRowAlgorithm.isEmpty() ||
            !p->m__PreparedColumnAlgorithm.isEmpty() )
    {
      if ( !p->m__PreparedRowAlgorithm.isEmpty() )
      {
        MAbstractRowCalculationAlgorithm *algorithm =
            p->m__PreparedRowAlgorithm.takeFirst();
        algorithm->calculate();
      }

      if ( !p->m__PreparedColumnAlgorithm.isEmpty() )
      {
        MAbstractColumnCalculationAlgorithm *algorithm =
            p->m__PreparedColumnAlgorithm.takeFirst();
        algorithm->calculate();
      }
    }
    qApp->processEvents();
  } while ( !p->m__PreparedRowAlgorithm.isEmpty() ||
            !p->m__PreparedColumnAlgorithm.isEmpty() );
}

void MCalculationalModel::declareValues()
{
  p = new MCalculationalModelPrivate( this );
}

void MCalculationalModel::addPreparedRowCalculationAlgorithm(
    MAbstractRowCalculationAlgorithm *algorithm )
{
  if ( p->m__PreparedRowAlgorithm.contains( algorithm ) ) return;

  p->m__PreparedRowAlgorithm << algorithm;
}

void MCalculationalModel::addPreparedColumnCalculationAlgorithm(
    MAbstractColumnCalculationAlgorithm *algorithm )
{
  if ( p->m__PreparedColumnAlgorithm.contains( algorithm ) ) return;

  p->m__PreparedColumnAlgorithm << algorithm;
}

void MCalculationalModel::columnLabelChanged( QVariant, QVariant )
{
  MCalculationalColumn *column = qobject_cast<MCalculationalColumn *>( sender() );

  if ( column == NULL ) return;

  emit headerData( column->column() );
}

void MCalculationalModel::columnDataChanged( int row, QVariant, QVariant )
{
  MCalculationalColumn *column = qobject_cast<MCalculationalColumn *>( sender() );

  if ( column == NULL ) return;

  emit dataChanged( index( row, column->column() ), index( row, column->column() ) );
}
