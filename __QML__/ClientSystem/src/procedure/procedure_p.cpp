#include "procedure_p.h"


Procedure_P::Procedure_P(Procedure *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Procedure * Procedure_P::p_dptr() const
{
    return qobject_cast<Procedure *>( parent() );
}
