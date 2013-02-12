#ifndef MROWCALCULATIONALGORITHM_H
#define MROWCALCULATIONALGORITHM_H

#include "mabstractrowcalculationalgorithm.h"

#include "lib_export.h"


class MRowCalculationAlgorithmPrivate;

class EXPORT MRowCalculationAlgorithm : public MAbstractRowCalculationAlgorithm
{
public:
  explicit MRowCalculationAlgorithm( MCalculationalRow *writableRow );

  bool setAlgorithm(const QString &algorithm , int decCount = -1 );
  const QString & algorithm() const;
  int decCount() const;


protected:
  void calculateColumn( int column );


private:
  MRowCalculationAlgorithmPrivate *p;
};

#endif // MROWCALCULATIONALGORITHM_H
