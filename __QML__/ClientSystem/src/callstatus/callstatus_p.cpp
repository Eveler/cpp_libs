#include "callstatus_p.h"


Callstatus_P::Callstatus_P(Callstatus *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Callstatus * Callstatus_P::p_dptr() const
{
    return qobject_cast<Callstatus *>( parent() );
}
