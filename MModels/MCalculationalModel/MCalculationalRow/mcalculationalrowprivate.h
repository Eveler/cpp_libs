#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>
#include <QVariant>


class MCalculationalModel;
class MCalculationalRow;
class MAbstractRowCalculationAlgorithm;

class MCalculationalRowPrivate
{
  friend class MCalculationalRow;
public:
  MCalculationalRowPrivate( MCalculationalModel *model );


private:
  MCalculationalModel *m__Model;

  QList<MAbstractRowCalculationAlgorithm *> m__RowAlgorithms;

  void declareValues();

  bool hasAlgorithmForSection( int section );
};

#endif // MCALCULATIONALROWPRIVATE_H
