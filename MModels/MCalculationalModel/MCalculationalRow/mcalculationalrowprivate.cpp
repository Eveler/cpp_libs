#include "mcalculationalrowprivate.h"

#include "mcalculationalmodel.h"


MCalculationalRowPrivate::MCalculationalRowPrivate( MCalculationalModel *model )
{
  declareValues();
  m__Model = model;
}

MCalculationalRowPrivate::~MCalculationalRowPrivate()
{
  m__Model = NULL;
  while ( !m__RowAlgorithms.isEmpty() )
  {
    MAbstractRowCalculationAlgorithm *algorithm = m__RowAlgorithms.takeFirst();
    delete algorithm;
    algorithm = NULL;
  }
}

void MCalculationalRowPrivate::declareValues()
{
  m__RowAlgorithms = QList<MAbstractRowCalculationAlgorithm *>();
}
