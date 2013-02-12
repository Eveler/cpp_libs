#include "mcalculationalrowprivate.h"

#include "mcalculationalmodel.h"
#include "mabstractrowcalculationalgorithm.h"
#include "mabstractcolumncalculationalgorithm.h"


MCalculationalRowPrivate::MCalculationalRowPrivate( MCalculationalModel *model )
{
  declareValues();
  m__Model = model;
}

void MCalculationalRowPrivate::declareValues()
{
  m__RowAlgorithms = QList<MAbstractRowCalculationAlgorithm *>();
}

bool MCalculationalRowPrivate::hasAlgorithmForSection( int section )
{
  foreach ( MAbstractRowCalculationAlgorithm *algorithm, m__RowAlgorithms )
    if ( algorithm->servedColumns().contains( section ) )
      return true;

  return false;
}
