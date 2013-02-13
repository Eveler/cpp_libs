#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>

#include "mabstractrowcalculationalgorithm.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalRow;

class MCalculationalRowPrivate
{
  friend class MCalculationalRow;
public:
  MCalculationalRowPrivate( MCalculationalModel *model );
  ~MCalculationalRowPrivate();


private:
  MCalculationalModel *m__Model;

  QList<MAbstractRowCalculationAlgorithm *> m__RowAlgorithms;

  void declareValues();
};

#endif // MCALCULATIONALROWPRIVATE_H
