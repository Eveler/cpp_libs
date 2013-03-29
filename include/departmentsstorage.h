#ifndef DEPARTMENTSSTORAGE_H
#define DEPARTMENTSSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/department_export_lib.h"


class Department;

typedef QList<Department *> DepartmentList;

class EXPORT_DEPARTMENT DepartmentsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static DepartmentsStorage * instance();

  const DepartmentList & departments() const;

  AbstractSimpleObjectList findByName( AbstractSimpleObjectList objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static DepartmentsStorage *m__Instance;

  explicit DepartmentsStorage(QObject *parent = 0);
};

#endif // DEPARTMENTSSTORAGE_H
