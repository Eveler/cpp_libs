#ifndef MROWCALCULATIONALGORITHM_H
#define MROWCALCULATIONALGORITHM_H

#include "mabstractcolumncalculationalgorithm.h"

#include "lib_export.h"


class MColumnCalculationAlgorithmPrivate;

class EXPORT MColumnCalculationAlgorithm : public MAbstractColumnCalculationAlgorithm
{
public:
  explicit MColumnCalculationAlgorithm( MCalculationalColumn *writableColumn );
  ~MColumnCalculationAlgorithm();

  bool setAlgorithm(const QString &algorithm , int decCount = -1 );
  const QString & algorithm() const;
  int decCount() const;


protected:
  void calculateRow( int row );


private:
  MColumnCalculationAlgorithmPrivate *p;
};

#endif // MROWCALCULATIONALGORITHM_H
