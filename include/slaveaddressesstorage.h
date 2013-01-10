#ifndef SLAVEADDRESSESSTORAGE_H
#define SLAVEADDRESSESSTORAGE_H

#include "abstractsimplestorage.h"

class SlaveAddressesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static SlaveAddressesStorage * instance();

signals:

public slots:

private:
  static SlaveAddressesStorage *m__Instance;

  explicit SlaveAddressesStorage(QObject *parent = 0);

};

#endif // SLAVEADDRESSESSTORAGE_H
