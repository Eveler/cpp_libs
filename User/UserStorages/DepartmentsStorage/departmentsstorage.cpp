#include "departmentsstorage.h"

DepartmentsStorage *DepartmentsStorage::m__Instance = NULL;

DepartmentsStorage * DepartmentsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DepartmentsStorage;

  return m__Instance;
}

DepartmentsStorage::DepartmentsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

