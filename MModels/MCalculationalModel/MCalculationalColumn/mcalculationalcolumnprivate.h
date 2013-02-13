#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>

#include "mabstractcolumncalculationalgorithm.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalColumn;

class MCalculationalColumnPrivate
{
  friend class MCalculationalColumn;
public:
  MCalculationalColumnPrivate( MCalculationalModel *model );
  ~MCalculationalColumnPrivate();


private:
  QVariant m__Label;
  QList<QVariant> m__Data;
  MCalculationalModel *m__Model;

  QList<MAbstractColumnCalculationAlgorithm *> m__ColumnAlgorithms;

  void declareValues();
};

#endif // MCALCULATIONALROWPRIVATE_H
