#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>
#include <QVariant>


class MCalculationalModel;
class MCalculationalRow;
class MAbstractRowCalculationAlgorithm;
class MAbstractColumnCalculationAlgorithm;

class MCalculationalRowPrivate
{
  friend class MCalculationalRow;
public:
  MCalculationalRowPrivate( MCalculationalModel *model );


private:
  QList<QVariant> m__Data;
  MCalculationalModel *m__Model;

  QList<MAbstractRowCalculationAlgorithm *> m__RowAlgorithms;
  QList<MAbstractColumnCalculationAlgorithm *> m__ColumnAlgorithms;

  void declareValues();
};

#endif // MCALCULATIONALROWPRIVATE_H
