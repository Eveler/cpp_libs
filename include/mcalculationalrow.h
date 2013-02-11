#ifndef MCALCULATIOANLROW_H
#define MCALCULATIOANLROW_H

#include <QObject>

#include "lib_export.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalRowPrivate;
class MAbstractRowCalculationAlgorithm;
class MAbstractColumnCalculationAlgorithm;

class EXPORT MCalculationalRow : public QObject
{
  friend class MCalculationalModel;
  friend class MAbstractRowCalculationAlgorithm;
  friend class MAbstractColumnCalculationAlgorithm;
  Q_OBJECT
public:
  int sectionCount() const;

  QVariant data( int section ) const;

  bool setData( int section, QVariant value );

  MCalculationalModel * model() const;

  int row();

signals:
  void dataChanged( int section, QVariant oldValue, QVariant newValue );


public slots:


private:
  MCalculationalRowPrivate *p;

  explicit MCalculationalRow( MCalculationalModel *model );
  ~MCalculationalRow();

  void insert( int section );
  void remove( int section );

  void addRowAlgorithm( MAbstractRowCalculationAlgorithm *algorithm );
  void addColumnAlgorithm( MAbstractColumnCalculationAlgorithm *algorithm );
};

#endif // MCALCULATIOANLROW_H
