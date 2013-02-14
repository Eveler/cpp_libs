#ifndef MCALCULATIOANLCOLUMN_H
#define MCALCULATIOANLCOLUMN_H

#include <QObject>

#include "lib_export.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalColumnPrivate;
class MAbstractColumnCalculationAlgorithm;
class MAbstractRowCalculationAlgorithm;

class EXPORT MCalculationalColumn : public QObject
{
  friend class MCalculationalModel;
  friend class MAbstractColumnCalculationAlgorithm;
  friend class MAbstractRowCalculationAlgorithm;
  Q_OBJECT
public:
  int sectionCount() const;

  QVariant label() const;

  void setLabel( QVariant label );

  QVariant data( int row ) const;

  bool setData( int row, const QVariant &value );

  MCalculationalModel * model() const;

  int column();

  const QList<MAbstractColumnCalculationAlgorithm *> & columnAlgorithms() const;
  MAbstractColumnCalculationAlgorithm * algorithmForRow( int row ) const;


signals:
  void labelChanged( QVariant oldValue, QVariant newValue );
  void dataChanged( int row, QVariant oldValue, QVariant newValue );


public slots:


private:
  MCalculationalColumnPrivate *p;

  explicit MCalculationalColumn( MCalculationalModel *model );
  ~MCalculationalColumn();

  void insert( int row );
  void remove( int row );

  void addColumnAlgorithm( MAbstractColumnCalculationAlgorithm *algorithm );

  void setDataPrivate( int row, QVariant value );
};

#endif // MCALCULATIOANLCOLUMN_H
