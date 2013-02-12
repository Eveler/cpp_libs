#ifndef MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H
#define MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H

#include <QList>


class MAbstractRowCalculationAlgorithm;
class MCalculationalColumn;
class MCalculationalRow;

class MAbstractRowCalculationAlgorithmPrivate
{
  friend class MAbstractRowCalculationAlgorithm;
public:
  MAbstractRowCalculationAlgorithmPrivate( MCalculationalRow *writableRow );


private:
  MCalculationalRow *m__WritableRow;
  QList<MCalculationalRow *> m__ReadableRows;
  QList<MCalculationalColumn *> m__Columns;
};

#endif // MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H
