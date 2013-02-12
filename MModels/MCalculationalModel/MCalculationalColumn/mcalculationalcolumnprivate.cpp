#include "mcalculationalcolumnprivate.h"

#include "mcalculationalmodel.h"
#include "mabstractrowcalculationalgorithm.h"
#include "mabstractcolumncalculationalgorithm.h"


MCalculationalColumnPrivate::MCalculationalColumnPrivate( MCalculationalModel *model )
{
  declareValues();
  m__Model = model;

  while ( m__Data.count() < model->rowCount() ) m__Data << QVariant();
}

void MCalculationalColumnPrivate::declareValues()
{
  m__Label = QVariant();
  m__Data = QList<QVariant>();
  m__ColumnAlgorithms = QList<MAbstractColumnCalculationAlgorithm *>();
}

bool MCalculationalColumnPrivate::hasAlgorithmForSection( int section )
{
//  foreach ( MAbstractRowCalculationAlgorithm *algorithm, m__RowAlgorithms )
//    if ( algorithm->servedColumns().contains( section ) )
//      return true;

  return false;
}
