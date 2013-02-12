#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>
#include <QVariant>


class MCalculationalModel;
class MCalculationalColumn;
class MAbstractColumnCalculationAlgorithm;

class MCalculationalColumnPrivate
{
  friend class MCalculationalColumn;
public:
  MCalculationalColumnPrivate( MCalculationalModel *model );


private:
  QVariant m__Label;
  QList<QVariant> m__Data;
  MCalculationalModel *m__Model;

  QList<MAbstractColumnCalculationAlgorithm *> m__ColumnAlgorithms;

  void declareValues();

  bool hasAlgorithmForSection( int section );
};

#endif // MCALCULATIONALROWPRIVATE_H
