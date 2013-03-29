#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "abstractsimpleobject.h"

#include "export/department_export_lib.h"

class Department_P;
class DepartmentsStorage;

class EXPORT_DEPARTMENT Department : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Department_P;
  friend class DepartmentsStorage;


public:
  ~Department();

  void setName( const QString &name );
  const QString & name() const;


signals:
  void nameChanged();


public slots:


private:
  Department_P *p;

  explicit Department( QVariant id, QObject *parent = 0 );
};

#endif // DEPARTMENT_H
