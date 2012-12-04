#ifndef DESTINATIONSSTORAGE_H
#define DESTINATIONSSTORAGE_H

#include "abstractsimplestorage.h"

class DestinationsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static DestinationsStorage * instance();

signals:

public slots:

private:
  static DestinationsStorage *m__Instance;

  explicit DestinationsStorage(QObject *parent = 0);

};

#endif // DESTINATIONSSTORAGE_H
