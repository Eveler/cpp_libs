#include "assessmenttype_p.h"


Assessmenttype_P::Assessmenttype_P(Assessmenttype *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Assessmenttype * Assessmenttype_P::p_dptr() const
{
    return qobject_cast<Assessmenttype *>( parent() );
}
