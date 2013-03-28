#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"


class EXPORT GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static GroupsStorage * instance();

  QList<AbstractSimpleObject *> findByName( QList<AbstractSimpleObject *> objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static GroupsStorage * m__Instance;

  explicit GroupsStorage(QObject *parent = 0);
};

#endif // GROUPSSTORAGE_H
