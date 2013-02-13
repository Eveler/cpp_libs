#ifndef MCOLUMNCALCULATIONALGORITHM_H
#define MCOLUMNCALCULATIONALGORITHM_H

#include "mabstractrowcalculationalgorithm.h"

#include "lib_export.h"


class MRowCalculationAlgorithmPrivate;

class EXPORT MRowCalculationAlgorithm : public MAbstractRowCalculationAlgorithm
{
public:
  explicit MRowCalculationAlgorithm( MCalculationalRow *writableRow );
  ~MRowCalculationAlgorithm();

  bool setAlgorithm(const QString &algorithm , int decCount = -1 );
  const QString & algorithm() const;
  int decCount() const;


protected:
  void calculateColumn( int column );


private:
  MRowCalculationAlgorithmPrivate *p;
};

#endif // MCOLUMNCALCULATIONALGORITHM_H
