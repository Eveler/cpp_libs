#ifndef MABSTRACTCOLUMNCALCULATIONALGORITHM_H
#define MABSTRACTCOLUMNCALCULATIONALGORITHM_H

#include <QObject>

#include "lib_export.h"

#include <QVariant>


class MAbstractColumnCalculationAlgorithmPrivate;
class MCalculationalColumn;
class MCalculationalModel;

class EXPORT MAbstractColumnCalculationAlgorithm : public QObject
{
  friend class MCalculationalModel;
  Q_OBJECT
public:
  explicit MAbstractColumnCalculationAlgorithm( MCalculationalColumn *writableColumn );
  ~MAbstractColumnCalculationAlgorithm();

  MCalculationalColumn * writableColumn() const;
  const QList<MCalculationalColumn *> & readableColumns() const;
  QList<int> servedRows() const;

  bool addReadableColumn( MCalculationalColumn *column );
  bool removeReadableColumn( MCalculationalColumn *column );
  void setServedRows( QList<int> rows );


signals:


public slots:


protected:
  void setData( int row, QVariant value );
  virtual void calculateRow( int row ) = 0;
  void calculate();


private:
  MAbstractColumnCalculationAlgorithmPrivate *p;


private slots:
  void dataChanged( int, QVariant, QVariant );
};

#endif // MABSTRACTCOLUMNCALCULATIONALGORITHM_H
