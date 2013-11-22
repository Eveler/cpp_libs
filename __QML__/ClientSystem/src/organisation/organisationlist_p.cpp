#include "organisationlist_p.h"


OrganisationList_P::OrganisationList_P( OrganisationList *parent ) :
    QObject(parent),
    m__Organisations(QList<Organisation *>())
{
}

OrganisationList_P::~OrganisationList_P()
{
}

OrganisationList * OrganisationList_P::p_dptr() const
{
    return qobject_cast<OrganisationList *>( parent() );
}

