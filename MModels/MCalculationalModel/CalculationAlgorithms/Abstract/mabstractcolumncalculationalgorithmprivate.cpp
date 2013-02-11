#include "mabstractcolumncalculationalgorithmprivate.h"

MAbstractColumnCalculationAlgorithmPrivate::MAbstractColumnCalculationAlgorithmPrivate(
    MCalculationalRow *writableRow )
{
  m__WritableRow = writableRow;
  m__ReadableRows = QList<MCalculationalRow *>();
  m__Columns = QList<int>();
}

void MAbstractColumnCalculationAlgorithmPrivate::reindexColumns()
{
  qStableSort( m__Columns.begin(), m__Columns.end() );
}
