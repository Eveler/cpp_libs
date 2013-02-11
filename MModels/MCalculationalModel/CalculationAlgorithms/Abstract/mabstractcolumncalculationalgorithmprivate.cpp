#include "mabstractcolumncalculationalgorithmprivate.h"

MAbstractColumnCalculationAlgorithmPrivate::MAbstractColumnCalculationAlgorithmPrivate(
    MCalculationalRow *writableRow )
{
  m__WritableRow = writableRow;
  m__WritableColumn = -1;
  m__ReadableColumns = QList<int>();
}
