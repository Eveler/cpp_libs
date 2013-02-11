#include "mcalculationalrowprivate.h"

#include "mcalculationalmodel.h"


MCalculationalRowPrivate::MCalculationalRowPrivate( MCalculationalModel *model )
{
  declareValues();

  while ( m__Data.count() < model->columnCount() ) m__Data << QVariant();
}

void MCalculationalRowPrivate::declareValues()
{
  m__Data = QList<QVariant>();
}
