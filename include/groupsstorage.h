#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"

class GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static GroupsStorage * instance();

signals:

public slots:

private:
  static GroupsStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Groups;

  explicit GroupsStorage(QObject *parent = 0);

};

#endif // GROUPSSTORAGE_H
