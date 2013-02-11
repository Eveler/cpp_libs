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
  QList<int> m__Columns;
  QList<MCalculationalRow *> m__ReadableRows;

  void reindexColumns();
};

#endif // MABSTRACTCOLUMNCALCULATIONALGORITHMPRIVATE_H
