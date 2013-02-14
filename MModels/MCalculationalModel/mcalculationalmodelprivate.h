#ifndef MCALCULATIONALMODELPRIVATE_H
#define MCALCULATIONALMODELPRIVATE_H

#include <QObject>

#include "mcalculationalcolumn.h"
#include "mcalculationalrow.h"

#include <QVariant>


class MAbstractRowCalculationAlgorithm;
class MAbstractColumnCalculationAlgorithm;
class MCalculationalModel;

class MCalculationalModelPrivate : public QObject
{
  friend class MCalculationalModel;
  Q_OBJECT
public:
  explicit MCalculationalModelPrivate(QObject *parent = 0);


signals:


public slots:


private:
  QList<MCalculationalColumn *> m__Columns;
  QList<MCalculationalRow *> m__Rows;

  QList<MAbstractRowCalculationAlgorithm *> m__PreparedRowAlgorithm;
  QList<MAbstractColumnCalculationAlgorithm *> m__PreparedColumnAlgorithm;

  void declareValues();
};

#endif // MCALCULATIONALMODELPRIVATE_H
