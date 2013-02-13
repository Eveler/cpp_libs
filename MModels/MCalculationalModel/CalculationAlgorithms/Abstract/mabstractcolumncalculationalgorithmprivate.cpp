#include "mabstractcolumncalculationalgorithmprivate.h"

MAbstractColumnCalculationAlgorithmPrivate::MAbstractColumnCalculationAlgorithmPrivate(
    MCalculationalColumn *writableColumn )
{
  m__WritableColumn = writableColumn;
  m__ReadableColumns = QList<MCalculationalColumn *>();
  m__Rows = QList<MCalculationalRow *>();
}

MAbstractColumnCalculationAlgorithmPrivate::~MAbstractColumnCalculationAlgorithmPrivate()
{
  m__WritableColumn = NULL;
  m__ReadableColumns.clear();
  m__Rows.clear();
}
