#ifndef MCOLUMNCALCULATIONALGORITHMPRIVATE_H
#define MCOLUMNCALCULATIONALGORITHMPRIVATE_H

#include <QString>


class MColumnCalculationAlgorithm;

class MColumnCalculationAlgorithmPrivate
{
  friend class MColumnCalculationAlgorithm;
public:
  MColumnCalculationAlgorithmPrivate();


private:
  QString m__Algorithm;
  int m__DecCount;
};

#endif // MCOLUMNCALCULATIONALGORITHMPRIVATE_H
