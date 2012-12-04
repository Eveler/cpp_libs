#ifndef CALLSSTORAGE_H
#define CALLSSTORAGE_H

#include "abstractsimplestorage.h"

class CallsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static CallsStorage * instance();

signals:

public slots:

private:
  static CallsStorage *m__Instance;

  explicit CallsStorage(QObject *parent = 0);

};

#endif // CALLSSTORAGE_H
