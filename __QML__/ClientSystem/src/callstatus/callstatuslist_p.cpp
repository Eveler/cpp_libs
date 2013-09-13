#include "callstatuslist_p.h"


CallstatusList_P::CallstatusList_P( CallstatusList *parent ) :
    QObject(parent),
    m__Callstatuss(QList<Callstatus *>())
{
}

CallstatusList_P::~CallstatusList_P()
{
}

CallstatusList * CallstatusList_P::p_dptr() const
{
    return qobject_cast<CallstatusList *>( parent() );
}

