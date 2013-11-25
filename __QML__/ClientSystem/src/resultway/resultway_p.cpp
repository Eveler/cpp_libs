#include "resultway_p.h"


Resultway_P::Resultway_P(Resultway *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Resultway * Resultway_P::p_dptr() const
{
    return qobject_cast<Resultway *>( parent() );
}
