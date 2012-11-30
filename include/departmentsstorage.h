#ifndef DEPARTMENTSSTORAGE_H
#define DEPARTMENTSSTORAGE_H

#include "abstractsimplestorage.h"
#include "department.h"

class DepartmentsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static DepartmentsStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static DepartmentsStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Departments;

  explicit DepartmentsStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // DEPARTMENTSSTORAGE_H
