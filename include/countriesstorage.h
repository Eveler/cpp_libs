#ifndef COUNTRIESSTORAGE_H
#define COUNTRIESSTORAGE_H

#include "abstractsimplestorage.h"

class CountriesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static CountriesStorage * instance();

signals:

public slots:

private:
  static CountriesStorage *m__Instance;

  explicit CountriesStorage(QObject *parent = 0);

};

#endif // COUNTRIESSTORAGE_H
