#include "doctype_p.h"


Doctype_P::Doctype_P(Doctype *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Doctype * Doctype_P::p_dptr() const
{
    return qobject_cast<Doctype *>( parent() );
}
