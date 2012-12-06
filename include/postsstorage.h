#ifndef POSTSSTORAGE_H
#define POSTSSTORAGE_H

#include "abstractsimplestorage.h"

class PostsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static PostsStorage * instance();

signals:

public slots:

private:
  static PostsStorage *m__Instance;

  explicit PostsStorage(QObject *parent = 0);

};

#endif // POSTSSTORAGE_H
