#include "humanlist_p.h"


HumanList_P::HumanList_P( HumanList *parent ) :
    QObject(parent),
    m__Humans(QList<Human *>())
{
}

HumanList_P::~HumanList_P()
{
}

HumanList * HumanList_P::p_dptr() const
{
    return qobject_cast<HumanList *>( parent() );
}

