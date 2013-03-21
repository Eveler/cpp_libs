#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"


class EXPORT GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static GroupsStorage * EXPORT instance();

signals:

public slots:

private:
  static GroupsStorage * EXPORT m__Instance;

  QList<AbstractSimpleObject *> m__Groups;

  explicit GroupsStorage(QObject *parent = 0);

};

#endif // GROUPSSTORAGE_H
