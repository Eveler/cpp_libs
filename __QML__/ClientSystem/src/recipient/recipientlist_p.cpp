#include "recipientlist_p.h"


RecipientList_P::RecipientList_P( RecipientList *parent ) :
    QObject(parent),
    m__Recipients(QList<Recipient *>())
{
}

RecipientList_P::~RecipientList_P()
{
}

RecipientList * RecipientList_P::p_dptr() const
{
    return qobject_cast<RecipientList *>( parent() );
}

