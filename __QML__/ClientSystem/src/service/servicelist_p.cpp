#include "servicelist_p.h"


ServiceList_P::ServiceList_P( ServiceList *parent ) :
    QObject(parent),
    m__Services(QList<Service *>())
{
}

ServiceList_P::~ServiceList_P()
{
}

ServiceList * ServiceList_P::p_dptr() const
{
    return qobject_cast<ServiceList *>( parent() );
}

