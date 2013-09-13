#include "human_p.h"


Human_P::Human_P(Human *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Human * Human_P::p_dptr() const
{
    return qobject_cast<Human *>( parent() );
}
