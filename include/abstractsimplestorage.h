#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include <QObject>

#include "lib_export.h"


class AbstractSimpleObject;

class EXPORT AbstractSimpleStorage : public QObject
{
  Q_OBJECT


public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  AbstractSimpleObject * addObject( QVariant id );
  const QList<AbstractSimpleObject *> & objects() const;
  void clear();

  QList<AbstractSimpleObject *> findById(
      QList<AbstractSimpleObject *> objects, QVariant id ) const;


signals:


public slots:


protected:
  virtual AbstractSimpleObject * createObject( QVariant id ) = 0;


private:
  QList<AbstractSimpleObject *> m__Objects;


private slots:
  void objectDestroyed( QObject *object );
};

#endif // ABSTRACTSIMPLESTORAGE_H
