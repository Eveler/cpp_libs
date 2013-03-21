#ifndef OFFICESSTORAGE_H
#define OFFICESSTORAGE_H

#include "abstractsimplestorage.h"

class EXPORT OfficesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static OfficesStorage * instance();

signals:

public slots:

private:
  static OfficesStorage *m__Instance;

  explicit OfficesStorage(QObject *parent = 0);

};

#endif // OFFICESSTORAGE_H
