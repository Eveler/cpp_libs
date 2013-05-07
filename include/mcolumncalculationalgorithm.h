#ifndef MROWCALCULATIONALGORITHM_H
#define MROWCALCULATIONALGORITHM_H

#include "mabstractcolumncalculationalgorithm.h"

#include "export/mmodels_export_lib.h"


class MColumnCalculationAlgorithmPrivate;

class EXPORT_MMODELS MColumnCalculationAlgorithm : public MAbstractColumnCalculationAlgorithm
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
