#include "recipient_p.h"

Recipient_P::Recipient_P(Recipient *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Recipient * Recipient_P::p_dptr() const
{
    return qobject_cast<Recipient *>( parent() );
}
