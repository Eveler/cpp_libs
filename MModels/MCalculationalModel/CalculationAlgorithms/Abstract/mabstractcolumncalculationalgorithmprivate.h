#ifndef MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H
#define MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H

#include <QList>


class MAbstractColumnCalculationAlgorithm;
class MCalculationalColumn;
class MCalculationalRow;

class MAbstractColumnCalculationAlgorithmPrivate
{
  friend class MAbstractColumnCalculationAlgorithm;
public:
  MAbstractColumnCalculationAlgorithmPrivate( MCalculationalColumn *writableColumn );
  ~MAbstractColumnCalculationAlgorithmPrivate();


private:
  MCalculationalColumn *m__WritableColumn;
  QList<MCalculationalColumn *> m__ReadableColumns;
  QList<MCalculationalRow *> m__Rows;
};

#endif // MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H
