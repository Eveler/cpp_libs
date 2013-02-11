#include "mcalculationalmodelprivate.h"


MCalculationalModelPrivate::MCalculationalModelPrivate(QObject *parent) :
  QObject(parent)
{
}

void MCalculationalModelPrivate::declareValues()
{
  m__Header = QList<QVariant>();
  m__Rows = QList<MCalculationalRow *>();
}
