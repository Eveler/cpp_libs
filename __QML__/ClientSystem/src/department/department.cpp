#include "department.h"

#include "department_p.h"
#include "departmentlist.h"


#define INFO_REF DepartmentInfo *info = static_cast<DepartmentInfo *>( p->p_dptr() );

Department::Department( DepartmentList *parent ) :
    QObject(parent), DepartmentInfo()
{
    p = new Department_P( this );
}

Department::Department( DepartmentList *parent, const DepartmentInfo &info ) :
    QObject(parent), DepartmentInfo(info)
{
    p = new Department_P( this );
}

Department::Department( DepartmentList *parent, Department *link ) :
    QObject(parent), DepartmentInfo()
{
    p = new Department_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Department::~Department()
{
    delete p;
    p = NULL;
}

DepartmentList * Department::departmentList() const
{
    return qobject_cast<DepartmentList *>( parent() );
}

int Department::index() const
{
    DepartmentList *pl = departmentList();
    if ( pl == NULL ) return -1;

    return pl->departmentIndex( p->p_dptr() );
}

QVariant Department::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Department::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Department::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Department::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
