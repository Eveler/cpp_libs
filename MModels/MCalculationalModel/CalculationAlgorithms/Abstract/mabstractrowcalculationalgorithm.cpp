#include "mabstractrowcalculationalgorithm.h"

#include "mabstractrowcalculationalgorithmprivate.h"
#include "mcalculationalcolumn.h"
#include "mcalculationalrow.h"
#include "mcalculationalmodel.h"
//#include "mcalculationalrowprivate.h"


MAbstractRowCalculationAlgorithm::MAbstractRowCalculationAlgorithm( MCalculationalRow *writableRow ) :
  QObject(writableRow)
{
  p = new MAbstractRowCalculationAlgorithmPrivate( writableRow );
  writableRow->addRowAlgorithm( this );
}

MCalculationalRow * MAbstractRowCalculationAlgorithm::writableRow() const
{
  return p->m__WritableRow;
}

const QList<MCalculationalRow *> & MAbstractRowCalculationAlgorithm::readableRows() const
{
  return p->m__ReadableRows;
}

QList<int> MAbstractRowCalculationAlgorithm::servedColumns() const
{
  QList<int> result = QList<int>();

  foreach ( MCalculationalColumn *column, p->m__Columns )
    result << column->column();

  return result;
}

bool MAbstractRowCalculationAlgorithm::addReadableRow( MCalculationalRow *row )
{
  if ( row == NULL || row->model() != p->m__WritableRow->model() ||
       p->m__ReadableRows.contains( row ) )
    return false;

  p->m__ReadableRows << row;

  calculate();

  return true;
}

bool MAbstractRowCalculationAlgorithm::removeReadableRow( MCalculationalRow *row )
{
  if ( row == NULL || !p->m__ReadableRows.contains( row ) )
    return false;

  p->m__ReadableRows.removeOne( row );

  calculate();

  return true;
}

void MAbstractRowCalculationAlgorithm::setServedColumns( QList<int> columns )
{
  while ( !p->m__Columns.isEmpty() )
  {
    MCalculationalColumn *c = p->m__Columns.takeFirst();
    disconnect( c, SIGNAL(dataChanged(int,QVariant,QVariant)),
                this, SLOT(dataChanged(int,QVariant,QVariant)) );
  }

  foreach ( int column, columns )
  {
    MCalculationalColumn *c = p->m__WritableRow->model()->column( column );
    if ( c != NULL )
    {
      p->m__Columns << c;
      connect( c, SIGNAL(dataChanged(int,QVariant,QVariant)),
               SLOT(dataChanged(int,QVariant,QVariant)) );

      calculateColumn( column );
    }
  }
}

void MAbstractRowCalculationAlgorithm::setData( int column, QVariant value )
{
  p->m__WritableRow->model()->column( column )->setDataPrivate(
        p->m__WritableRow->row(), value );
}

void MAbstractRowCalculationAlgorithm::calculate()
{
  foreach ( MCalculationalColumn *column, p->m__Columns ) calculateColumn( column->column() );
}

void MAbstractRowCalculationAlgorithm::dataChanged( int /*row*/, QVariant /*oldVal*/, QVariant /*newVal*/ )
{
    MCalculationalColumn *column = qobject_cast<MCalculationalColumn *>( sender() );

    if ( column == NULL ) return;

    calculateColumn( column->column() );
}
