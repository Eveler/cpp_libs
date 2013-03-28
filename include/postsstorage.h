#ifndef POSTSSTORAGE_H
#define POSTSSTORAGE_H

#include "abstractsimplestorage.h"


class EXPORT PostsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static PostsStorage * instance();

  QList<AbstractSimpleObject *> findByName( QList<AbstractSimpleObject *> objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static PostsStorage *m__Instance;

  explicit PostsStorage(QObject *parent = 0);
};

#endif // POSTSSTORAGE_H
