#include "departmentsstorage.h"

DepartmentsStorage *DepartmentsStorage::m__Instance = NULL;

DepartmentsStorage * DepartmentsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DepartmentsStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & DepartmentsStorage::objects() const
{
  return m__Departments;
}

DepartmentsStorage::DepartmentsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void DepartmentsStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
}

void DepartmentsStorage::recordAdded( MFCRecord *record, int index )
{
  Department *department = new Department( this );
  setObjectData( department, record );
  m__Departments.insert( index, department );
}

void DepartmentsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  AbstractSimpleObject *obj = m__Departments.takeAt( index );
  delete obj;
}

