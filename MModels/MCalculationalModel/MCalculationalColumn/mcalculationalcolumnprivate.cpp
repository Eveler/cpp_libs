#include "mcalculationalcolumnprivate.h"

#include "mcalculationalmodel.h"


MCalculationalColumnPrivate::MCalculationalColumnPrivate( MCalculationalModel *model )
{
  declareValues();
  m__Model = model;

  while ( m__Data.count() < model->rowCount() ) m__Data << QVariant();
}

MCalculationalColumnPrivate::~MCalculationalColumnPrivate()
{
  m__Data.clear();
  m__Model = NULL;
  while ( !m__ColumnAlgorithms.isEmpty() )
  {
    MAbstractColumnCalculationAlgorithm *algorithm = m__ColumnAlgorithms.takeFirst();
    delete algorithm;
    algorithm = NULL;
  }
}

void MCalculationalColumnPrivate::declareValues()
{
  m__Label = QVariant();
  m__Data = QList<QVariant>();
  m__ColumnAlgorithms = QList<MAbstractColumnCalculationAlgorithm *>();
}
