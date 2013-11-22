#include "organisationlist.h"

#include "organisationlist_p.h"


OrganisationList::OrganisationList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new OrganisationList_P( this );
}

OrganisationList::~OrganisationList()
{
    while ( !p->m__Organisations.isEmpty() )
    {
        Organisation *organisation = p->m__Organisations.takeFirst();
        disconnect( organisation, SIGNAL(destroyed()), this, SLOT(organisationDestroyed()) );
        delete organisation;
        organisation = NULL;
    }

    delete p;
    p = NULL;
}

int OrganisationList::count() const
{
    return p->m__Organisations.count();
}

void OrganisationList::clear() const
{
    while ( !p->m__Organisations.isEmpty() )
    {
        Organisation *organisation = p->m__Organisations.takeFirst();
        disconnect( organisation, SIGNAL(destroyed()), this, SLOT(organisationDestroyed()) );
        delete organisation;
        organisation = NULL;
    }
    emit countChanged();
}

Organisation * OrganisationList::organisation( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Organisations[index];
}

int OrganisationList::organisationIndex( Organisation *organisation ) const
{
    return p->m__Organisations.indexOf( organisation );
}

Organisation * OrganisationList::addLink( Organisation *link ) const
{
    if ( p->m__Organisations.contains( link ) ) return link;

    Organisation *newOrganisation = new Organisation( p->p_dptr(), link );
    p->m__Organisations << newOrganisation;
    connect( newOrganisation, SIGNAL(destroyed()), SLOT(organisationDestroyed()) );
    emit organisationAdded( newOrganisation );
    emit countChanged();
    return newOrganisation;
}

void OrganisationList::receivedOrganisationInfo( OrganisationInfo organisationInfo ) const
{
    Organisation *newOrganisation = new Organisation( p->p_dptr(), organisationInfo );
    p->m__Organisations << newOrganisation;
    connect( newOrganisation, SIGNAL(destroyed()), SLOT(organisationDestroyed()) );
    emit organisationAdded( newOrganisation );
    emit countChanged();
}

void OrganisationList::organisationDestroyed()
{
    Organisation *organisation = qobject_cast<Organisation *>( sender() );
    int index = p->m__Organisations.indexOf( organisation );
    p->m__Organisations.removeAt( index );
    emit organisationRemoved( index );
    emit countChanged();
}
