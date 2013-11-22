#include "organisation_p.h"


Organisation_P::Organisation_P(Organisation *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Organisation * Organisation_P::p_dptr() const
{
    return qobject_cast<Organisation *>( parent() );
}
