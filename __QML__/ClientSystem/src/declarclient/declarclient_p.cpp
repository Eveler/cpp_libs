#include "declarclient_p.h"


DeclarClient_P::DeclarClient_P(DeclarClient *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

DeclarClient * DeclarClient_P::p_dptr() const
{
    return qobject_cast<DeclarClient *>( parent() );
}
