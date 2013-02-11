#include "mcalculationalrowprivate.h"

MCalculationalRowPrivate::MCalculationalRowPrivate( int count )
{
  declareValues();

  while ( m__Data.count() < count ) m__Data << QVariant();
}

void MCalculationalRowPrivate::declareValues()
{
  m__Data = QList<QVariant>();
}
