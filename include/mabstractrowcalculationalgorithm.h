#ifndef MABSTRACTROWCALCULATIONALGORITHM_H
#define MABSTRACTROWCALCULATIONALGORITHM_H

#include <QObject>

#include "export/mmodels_export_lib.h"

#include <QVariant>


class MAbstractRowCalculationAlgorithmPrivate;
class MCalculationalRow;
class MCalculationalModel;

class EXPORT_MMODELS MAbstractRowCalculationAlgorithm : public QObject
{
  friend class MCalculationalModel;
  Q_OBJECT
public:
  explicit MAbstractRowCalculationAlgorithm( MCalculationalRow *writableRow );
  ~MAbstractRowCalculationAlgorithm();

  MCalculationalRow * writableRow() const;
  const QList<MCalculationalRow *> & readableRows() const;
  QList<int> servedColumns() const;

  bool addReadableRow( MCalculationalRow *row );
  bool removeReadableRow( MCalculationalRow *row );
  void setServedColumns( QList<int> columns );


signals:


public slots:


protected:
  void setData( int column, QVariant value );
  virtual void calculateColumn( int column ) = 0;
  void calculate();


private:
  MAbstractRowCalculationAlgorithmPrivate *p;


private slots:
  void dataChanged( int, QVariant, QVariant );
};

#endif // MABSTRACTROWCALCULATIONALGORITHM_H
