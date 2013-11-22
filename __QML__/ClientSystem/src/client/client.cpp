#include "client.h"

#include "client_p.h"
#include "clientlist.h"


#define INFO_REF ClientInfo *info = static_cast<ClientInfo *>( p->p_dptr() );

Client::Client( ClientList *parent ) :
    QObject(parent), ClientInfo()
{
    p = new Client_P( this );
}

Client::Client( ClientList *parent, const ClientInfo &info ) :
    QObject(parent), ClientInfo(info)
{
    p = new Client_P( this );
}

Client::Client( ClientList *parent, Client *link ) :
    QObject(parent), ClientInfo()
{
    p = new Client_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Client::~Client()
{
    delete p;
    p = NULL;
}

ClientList * Client::clientList() const
{
    return qobject_cast<ClientList *>( parent() );
}

int Client::index() const
{
    ClientList *pl = clientList();
    if ( pl == NULL ) return -1;

    return pl->clientIndex( p->p_dptr() );
}

QVariant Client::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Client::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

QVariant Client::organisationIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->organisationIdentifier();
    return info->organisationIdentifier();
}

void Client::setOrganisationIdentifier( QVariant organisationIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setOrganisationIdentifier( organisationIdentifier );
    else info->setOrganisationIdentifier( organisationIdentifier );
    emit organisationIdentifierChanged();
}

QVariant Client::humanIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->humanIdentifier();
    return info->humanIdentifier();
}

void Client::setHumanIdentifier( QVariant humanIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setHumanIdentifier( humanIdentifier );
    else info->setHumanIdentifier( humanIdentifier );
    emit humanIdentifierChanged();
}
