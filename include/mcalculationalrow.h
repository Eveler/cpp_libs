#ifndef MCALCULATIOANLROW_H
#define MCALCULATIOANLROW_H

#include <QObject>

#include "export/mmodels_export_lib.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalRowPrivate;
class MAbstractRowCalculationAlgorithm;

class EXPORT_MMODELS MCalculationalRow : public QObject
{
  friend class MCalculationalModel;
  friend class MAbstractRowCalculationAlgorithm;
  Q_OBJECT
public:
  int sectionCount() const;

  QVariant data( int column );

  bool setData( int column, const QVariant &value );

  MCalculationalModel * model() const;

  int row();

  const QList<MAbstractRowCalculationAlgorithm *> & rowAlgorithms() const;
  MAbstractRowCalculationAlgorithm * algorithmForColumn( int column ) const;


signals:


public slots:


private:
  MCalculationalRowPrivate *p;

  explicit MCalculationalRow( MCalculationalModel *model );
  ~MCalculationalRow();

  void addRowAlgorithm( MAbstractRowCalculationAlgorithm *algorithm );
};

#endif // MCALCULATIOANLROW_H
