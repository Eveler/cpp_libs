#ifndef MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H
#define MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H

#include <QList>


class MAbstractRowCalculationAlgorithm;
class MCalculationalRow;

class MAbstractRowCalculationAlgorithmPrivate
{
  friend class MAbstractRowCalculationAlgorithm;
public:
  MAbstractRowCalculationAlgorithmPrivate( MCalculationalRow *writableRow );


private:
  MCalculationalRow *m__WritableRow;
  QList<MCalculationalRow *> m__ReadableRows;
  QList<int> m__Columns;
};

#endif // MABSTRACTROWCALCULATIONALGORITHMPRIVATE_H
