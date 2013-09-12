#include "department_p.h"


Department_P::Department_P(Department *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Department * Department_P::p_dptr() const
{
    return qobject_cast<Department *>( parent() );
}
