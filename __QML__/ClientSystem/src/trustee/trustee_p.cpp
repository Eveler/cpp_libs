#include "trustee_p.h"


Trustee_P::Trustee_P(Trustee *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Trustee * Trustee_P::p_dptr() const
{
    return qobject_cast<Trustee *>( parent() );
}
