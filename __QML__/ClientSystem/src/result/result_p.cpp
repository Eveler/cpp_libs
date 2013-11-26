#include "result_p.h"


Result_P::Result_P(Result *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Result * Result_P::p_dptr() const
{
    return qobject_cast<Result *>( parent() );
}
