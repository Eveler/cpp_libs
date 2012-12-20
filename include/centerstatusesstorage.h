#ifndef CENTERSTATUSESSTORAGE_H
#define CENTERSTATUSESSTORAGE_H

#include "abstractsimplestorage.h"

class CenterStatusesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static CenterStatusesStorage * instance();

signals:

public slots:

private:
  static CenterStatusesStorage *m__Instance;

  explicit CenterStatusesStorage(QObject *parent = 0);

};

#endif // CENTERSTATUSESSTORAGE_H
