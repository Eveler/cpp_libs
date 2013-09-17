#include "departmentlist_p.h"


DepartmentList_P::DepartmentList_P( DepartmentList *parent ) :
    QObject(parent),
    m__Departments(QList<Department *>())
{
}

DepartmentList_P::~DepartmentList_P()
{
}

DepartmentList * DepartmentList_P::p_dptr() const
{
    return qobject_cast<DepartmentList *>( parent() );
}

