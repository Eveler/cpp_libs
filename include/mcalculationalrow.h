#ifndef MCALCULATIOANLROW_H
#define MCALCULATIOANLROW_H

#include <QObject>

#include "lib_export.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalRowPrivate;
class MAbstractRowCalculationAlgorithm;

class EXPORT MCalculationalRow : public QObject
{
  friend class MCalculationalModel;
  friend class MAbstractRowCalculationAlgorithm;
  Q_OBJECT
public:
  int sectionCount() const;

  QVariant data( int column );

  bool setData( int column, QVariant value );

  MCalculationalModel * model() const;

  int row();

signals:


public slots:


private:
  MCalculationalRowPrivate *p;

  explicit MCalculationalRow( MCalculationalModel *model );
  ~MCalculationalRow();

  void addRowAlgorithm( MAbstractRowCalculationAlgorithm *algorithm );
};

#endif // MCALCULATIOANLROW_H
