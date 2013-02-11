#ifndef MCALCULATIONALROWPRIVATE_H
#define MCALCULATIONALROWPRIVATE_H

#include <QList>
#include <QVariant>


class MCalculationalRow;

class MCalculationalRowPrivate
{
  friend class MCalculationalRow;
public:
  MCalculationalRowPrivate( int count );


private:
  QList<QVariant> m__Data;

  void declareValues();
};

#endif // MCALCULATIONALROWPRIVATE_H
