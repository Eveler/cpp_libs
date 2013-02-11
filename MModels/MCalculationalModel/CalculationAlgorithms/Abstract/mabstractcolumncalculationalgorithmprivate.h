#ifndef MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H
#define MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H

#include <QList>


class MAbstractColumnCalculationAlgorithm;
class MCalculationalRow;

class MAbstractColumnCalculationAlgorithmPrivate
{
  friend class MAbstractColumnCalculationAlgorithm;
public:
  MAbstractColumnCalculationAlgorithmPrivate( MCalculationalRow *writableRow );


private:
  MCalculationalRow *m__WritableRow;
  int m__WritableColumn;
  QList<int> m__ReadableColumns;
};

#endif // MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H
