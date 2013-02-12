#ifndef MROWCALCULATIONALGORITHMPRIVATE_H
#define MROWCALCULATIONALGORITHMPRIVATE_H

#include <QString>


class MRowCalculationAlgorithm;

class MRowCalculationAlgorithmPrivate
{
  friend class MRowCalculationAlgorithm;
public:
  MRowCalculationAlgorithmPrivate();


private:
  QString m__Algorithm;
  int m__DecCount;
};

#endif // MROWCALCULATIONALGORITHMPRIVATE_H
