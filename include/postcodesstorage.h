#ifndef POSTCODESSTORAGE_H
#define POSTCODESSTORAGE_H

#include "abstractsimplestorage.h"

class PostcodesStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static PostcodesStorage * instance();

signals:

public slots:

private:
  static PostcodesStorage *m__Instance;

  explicit PostcodesStorage(QObject *parent = 0);

};

#endif // POSTCODESSTORAGE_H
