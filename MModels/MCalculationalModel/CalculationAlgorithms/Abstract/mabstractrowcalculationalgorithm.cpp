#include "mabstractrowcalculationalgorithm.h"

#include "mabstractrowcalculationalgorithmprivate.h"
#include "mcalculationalrow.h"
#include "mcalculationalrowprivate.h"


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

const QList<int> & MAbstractRowCalculationAlgorithm::servedColumns() const
{
  return p->m__Columns;
}

bool MAbstractRowCalculationAlgorithm::addReadableRow( MCalculationalRow *row )
{
  if ( row == NULL || row->model() != p->m__WritableRow->model() ||
       p->m__ReadableRows.contains( row ) )
    return false;

  p->m__ReadableRows << row;

  return true;
}

bool MAbstractRowCalculationAlgorithm::removeReadableRow( MCalculationalRow *row )
{
  if ( row == NULL || !p->m__ReadableRows.contains( row ) )
    return false;

  p->m__ReadableRows.removeOne( row );

  return true;
}

void MAbstractRowCalculationAlgorithm::setServedColumns( QList<int> columns )
{
  p->m__Columns = columns;

  calculate();
}

void MAbstractRowCalculationAlgorithm::calculate()
{
  foreach ( int column, p->m__Columns ) calculateColumn( column );
}
