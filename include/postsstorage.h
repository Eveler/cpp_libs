#ifndef POSTSSTORAGE_H
#define POSTSSTORAGE_H

#include "abstractsimplestorage.h"

#include "lib_export.h"


class EXPORT PostsStorage : public AbstractSimpleStorage
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
