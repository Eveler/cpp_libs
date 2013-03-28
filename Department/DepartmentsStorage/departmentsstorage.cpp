#include "departmentsstorage.h"

#include "department.h"


DepartmentsStorage *DepartmentsStorage::m__Instance = NULL;

DepartmentsStorage * DepartmentsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DepartmentsStorage;

  return m__Instance;
}

QList<AbstractSimpleObject *> DepartmentsStorage::findByName(
    QList<AbstractSimpleObject *> objects, QString name )
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Department *department = qobject_cast<Department *>( object );
    if ( department->name() == name )
      result << object;
  }

  return result;
}

AbstractSimpleObject * DepartmentsStorage::createObject( QVariant id )
{
  return new Department( id, this );
}

DepartmentsStorage::DepartmentsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
