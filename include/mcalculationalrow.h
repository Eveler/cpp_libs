#ifndef MCALCULATIOANLROW_H
#define MCALCULATIOANLROW_H

#include <QObject>

#include "lib_export.h"

#include <QVariant>


class MCalculationalModel;
class MCalculationalRowPrivate;

class EXPORT MCalculationalRow : public QObject
{
  friend class MCalculationalModel;
  Q_OBJECT
public:
  int sectionCount() const;

  QVariant data( int section ) const;

  bool setData( int section, QVariant value );

signals:
  void dataChanged( int section, QVariant oldValue, QVariant newValue );


public slots:


private:
  MCalculationalRowPrivate *p;

  explicit MCalculationalRow( int count, QObject *parent = 0 );
  ~MCalculationalRow();

  void insert( int section );
  void remove( int section );
};

#endif // MCALCULATIOANLROW_H
