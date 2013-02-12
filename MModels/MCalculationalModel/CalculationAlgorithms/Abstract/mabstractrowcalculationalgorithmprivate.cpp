#include "mabstractrowcalculationalgorithmprivate.h"

MAbstractRowCalculationAlgorithmPrivate::MAbstractRowCalculationAlgorithmPrivate(
    MCalculationalRow *writableRow )
{
  m__WritableRow = writableRow;
  m__ReadableRows = QList<MCalculationalRow *>();
  m__Columns = QList<MCalculationalColumn *>();
}
