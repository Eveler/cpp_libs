#include "client_p.h"


Client_P::Client_P(Client *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Client * Client_P::p_dptr() const
{
    return qobject_cast<Client *>( parent() );
}
