#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include <QObject>

#include "export/mfccore_export_lib.h"


class AbstractSimpleObject;

typedef QList<AbstractSimpleObject *> AbstractSimpleObjectList;

class EXPORT_MFCCORE AbstractSimpleStorage : public QObject
{
  Q_OBJECT


public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  AbstractSimpleObject * addObject( QVariant id );
  const AbstractSimpleObjectList & objects() const;
  void clear();

  QList<AbstractSimpleObject *> findById(
      QList<AbstractSimpleObject *> objects, QVariant id ) const;


signals:


public slots:


protected:
  virtual AbstractSimpleObject * createObject( QVariant id ) = 0;


private:
  AbstractSimpleObjectList m__Objects;


private slots:
  void objectDestroyed( QObject *object );
};

#endif // ABSTRACTSIMPLESTORAGE_H
