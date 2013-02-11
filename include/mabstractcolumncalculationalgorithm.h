#ifndef MABSTRACTCOLUMNCALCULATIONALGORITHM_H
#define MABSTRACTCOLUMNCALCULATIONALGORITHM_H

#include <QObject>


class MAbstractColumnCalculationAlgorithmPrivate;
class MCalculationalRow;

class MAbstractColumnCalculationAlgorithm : public QObject
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
