#ifndef MCOLUMNCALCULATIONALGORITHM_H
#define MCOLUMNCALCULATIONALGORITHM_H

#include "mabstractrowcalculationalgorithm.h"

#include "export/mmodels_export_lib.h"


class MRowCalculationAlgorithmPrivate;

class EXPORT_MMODELS MRowCalculationAlgorithm : public MAbstractRowCalculationAlgorithm
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
