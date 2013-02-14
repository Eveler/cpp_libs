#include "mcalculationalmodelprivate.h"


MCalculationalModelPrivate::MCalculationalModelPrivate(QObject *parent) :
  QObject(parent)
{
  declareValues();
}

void MCalculationalModelPrivate::declareValues()
{
  m__Columns = QList<MCalculationalColumn *>();
  m__Rows = QList<MCalculationalRow *>();

  m__PreparedRowAlgorithm = QList<MAbstractRowCalculationAlgorithm *>();
  m__PreparedColumnAlgorithm = QList<MAbstractColumnCalculationAlgorithm *>();
}
