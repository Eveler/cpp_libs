#include "declar_p.h"


Declar_P::Declar_P(Declar *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Declar * Declar_P::p_dptr() const
{
    return qobject_cast<Declar *>( parent() );
}
