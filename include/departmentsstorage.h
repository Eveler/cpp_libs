#ifndef DEPARTMENTSSTORAGE_H
#define DEPARTMENTSSTORAGE_H

#include "abstractsimplestorage.h"


class EXPORT DepartmentsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static DepartmentsStorage * instance();

  QList<AbstractSimpleObject *> findByName( QList<AbstractSimpleObject *> objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static DepartmentsStorage *m__Instance;

  explicit DepartmentsStorage(QObject *parent = 0);
};

#endif // DEPARTMENTSSTORAGE_H
