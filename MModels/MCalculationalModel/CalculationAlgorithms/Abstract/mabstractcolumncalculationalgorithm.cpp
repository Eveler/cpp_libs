#include "mabstractcolumncalculationalgorithm.h"

#include "mabstractcolumncalculationalgorithmprivate.h"
#include "mcalculationalcolumn.h"
#include "mcalculationalrow.h"
#include "mcalculationalmodel.h"


MAbstractColumnCalculationAlgorithm::MAbstractColumnCalculationAlgorithm(
    MCalculationalColumn *writableColumn) :
  QObject(writableColumn)
{
  p = new MAbstractColumnCalculationAlgorithmPrivate( writableColumn );
  writableColumn->addColumnAlgorithm( this );
}

MAbstractColumnCalculationAlgorithm::~MAbstractColumnCalculationAlgorithm()
{
  delete p;
  p = NULL;
}

MCalculationalColumn * MAbstractColumnCalculationAlgorithm::writableColumn() const
{
  return p->m__WritableColumn;
}

const QList<MCalculationalColumn *> &
MAbstractColumnCalculationAlgorithm::readableColumns() const
{
  return p->m__ReadableColumns;
}

QList<int> MAbstractColumnCalculationAlgorithm::servedRows() const
{
  QList<int> result = QList<int>();

  foreach ( MCalculationalRow *row, p->m__Rows )
    result << row->row();

  return result;
}

bool MAbstractColumnCalculationAlgorithm::addReadableColumn( MCalculationalColumn *column )
{
  if ( column == NULL || column->model() != p->m__WritableColumn->model() ||
       p->m__ReadableColumns.contains( column ) )
    return false;

  p->m__ReadableColumns << column;
  connect( column, SIGNAL(dataChanged(int,QVariant,QVariant)),
           SLOT(dataChanged(int,QVariant,QVariant)) );

  calculate();

  return true;
}

bool MAbstractColumnCalculationAlgorithm::removeReadableColumn( MCalculationalColumn *column )
{
  if ( column == NULL || !p->m__ReadableColumns.contains( column ) )
    return false;

  p->m__ReadableColumns.removeOne( column );
  disconnect( column, SIGNAL(dataChanged(int,QVariant,QVariant)),
              this, SLOT(dataChanged(int,QVariant,QVariant)) );

  calculate();

  return true;
}

void MAbstractColumnCalculationAlgorithm::setServedRows( QList<int> rows )
{
  while ( !p->m__Rows.isEmpty() )
  {
    MCalculationalRow *r = p->m__Rows.takeFirst();
    disconnect( r, SIGNAL(dataChanged(int,QVariant,QVariant)),
                this, SLOT(dataChanged(int,QVariant,QVariant)) );
  }

  foreach ( int row, rows )
  {
    MCalculationalRow *r = p->m__WritableColumn->model()->row( row );
    if ( r != NULL )
    {
      p->m__Rows << r;

      calculateRow( row );
    }
  }
}

void MAbstractColumnCalculationAlgorithm::setData( int row, QVariant value )
{
  p->m__WritableColumn->setDataPrivate( row, value );
}

void MAbstractColumnCalculationAlgorithm::calculate()
{
  foreach ( MCalculationalRow *row, p->m__Rows ) calculateRow( row->row() );
}

void MAbstractColumnCalculationAlgorithm::dataChanged(
    int row, QVariant /*oldVal*/, QVariant /*newVal*/ )
{
    MCalculationalColumn *column = qobject_cast<MCalculationalColumn *>( sender() );

    if ( column == NULL ) return;

    foreach ( MCalculationalRow *r, p->m__Rows )
      if ( r->row() == row ) calculateRow( row );
}
