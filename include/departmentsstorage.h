#ifndef DEPARTMENTSSTORAGE_H
#define DEPARTMENTSSTORAGE_H

#include "abstractsimplestorage.h"

class DepartmentsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static DepartmentsStorage * instance();

signals:

public slots:

private:
  static DepartmentsStorage *m__Instance;

  explicit DepartmentsStorage(QObject *parent = 0);

};

#endif // DEPARTMENTSSTORAGE_H
