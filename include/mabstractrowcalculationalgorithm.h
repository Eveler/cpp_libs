#ifndef MABSTRACTROWCALCULATIONALGORITHM_H
#define MABSTRACTROWCALCULATIONALGORITHM_H

#include <QObject>


class MAbstractRowCalculationAlgorithmPrivate;
class MCalculationalRow;

class MAbstractRowCalculationAlgorithm : public QObject
{
  Q_OBJECT
public:
  explicit MAbstractRowCalculationAlgorithm( MCalculationalRow *writableRow );

  MCalculationalRow * writableRow() const;
  const QList<MCalculationalRow *> & readableRows() const;
  const QList<int> & servedColumns() const;

  bool addReadableRow( MCalculationalRow *row );
  bool removeReadableRow( MCalculationalRow *row );
  void setServedColumns( QList<int> columns );


signals:

public slots:


protected:
  virtual void calculateColumn( int column ) = 0;


private:
  MAbstractRowCalculationAlgorithmPrivate *p;

  void calculate();
};

#endif // MABSTRACTROWCALCULATIONALGORITHM_H
