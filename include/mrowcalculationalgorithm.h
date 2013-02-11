#ifndef MROWCALCULATIONALGORITHM_H
#define MROWCALCULATIONALGORITHM_H

#include "mabstractrowcalculationalgorithm.h"


class MRowCalculationAlgorithmPrivate;

class MRowCalculationAlgorithm : public MAbstractRowCalculationAlgorithm
{
public:
  explicit MRowCalculationAlgorithm( MCalculationalRow *writableRow );

  bool setAlgorithm( const QString &algorithm );
  const QString & algorithm() const;


protected:
  void calculateColumn( int column );


private:
  MRowCalculationAlgorithmPrivate *p;
};

#endif // MROWCALCULATIONALGORITHM_H
