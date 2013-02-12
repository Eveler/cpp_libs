#ifndef MABSTRACTCOLUMNCALCULATIONALGORITHM_H
#define MABSTRACTCOLUMNCALCULATIONALGORITHM_H

#include <QObject>

#include "lib_export.h"


class MAbstractColumnCalculationAlgorithmPrivate;
class MCalculationalRow;

class EXPORT MAbstractColumnCalculationAlgorithm : public QObject
{
  Q_OBJECT
public:
  explicit MAbstractColumnCalculationAlgorithm( MCalculationalRow *writableRow );


signals:


public slots:


private:
  MAbstractColumnCalculationAlgorithmPrivate *p;
};

#endif // MABSTRACTCOLUMNCALCULATIONALGORITHM_H
