#include "mabstractcolumncalculationalgorithm.h"

#include "mabstractcolumncalculationalgorithmprivate.h"
#include "mcalculationalrow.h"


MAbstractColumnCalculationAlgorithm::MAbstractColumnCalculationAlgorithm(
    MCalculationalRow *writableRow) :
  QObject(writableRow)
{
  p = new MAbstractColumnCalculationAlgorithmPrivate( writableRow );
}
