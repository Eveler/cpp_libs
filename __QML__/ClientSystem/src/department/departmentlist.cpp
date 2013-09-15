#include "departmentlist.h"

#include "departmentlist_p.h"


DepartmentList::DepartmentList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new DepartmentList_P( this );
}

DepartmentList::~DepartmentList()
{
    while ( !p->m__Departments.isEmpty() )
    {
        Department *department = p->m__Departments.takeFirst();
        disconnect( department, SIGNAL(destroyed()), this, SLOT(departmentDestroyed()) );
        delete department;
        department = NULL;
    }

    delete p;
    p = NULL;
}

int DepartmentList::count() const
{
    return p->m__Departments.count();
}

void DepartmentList::clear() const
{
    while ( !p->m__Departments.isEmpty() )
    {
        Department *department = p->m__Departments.takeFirst();
        disconnect( department, SIGNAL(destroyed()), this, SLOT(departmentDestroyed()) );
        delete department;
        department = NULL;
    }
    emit countChanged();
}

Department * DepartmentList::department( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Departments[index];
}

int DepartmentList::departmentIndex( Department *department ) const
{
    return p->m__Departments.indexOf( department );
}

Department * DepartmentList::addLink( Department *link ) const
{
    if ( p->m__Departments.contains( link ) ) return link;

    Department *newDepartment = new Department( p->p_dptr(), link );
    p->m__Departments << newDepartment;
    connect( newDepartment, SIGNAL(destroyed()), SLOT(departmentDestroyed()) );
    emit departmentAdded( newDepartment );
    emit countChanged();
    return newDepartment;
}

void DepartmentList::receivedDepartmentInfo( DepartmentInfo departmentInfo ) const
{
    Department *newDepartment = new Department( p->p_dptr(), departmentInfo );
    p->m__Departments << newDepartment;
    connect( newDepartment, SIGNAL(destroyed()), SLOT(departmentDestroyed()) );
    emit departmentAdded( newDepartment );
    emit countChanged();
}

void DepartmentList::departmentDestroyed()
{
    Department *department = qobject_cast<Department *>( sender() );
    int index = p->m__Departments.indexOf( department );
    p->m__Departments.removeAt( index );
    emit departmentRemoved( index );
    emit countChanged();
}
