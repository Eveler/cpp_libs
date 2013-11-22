#include "declarclient.h"

#include "declarclient_p.h"
#include "declarclientlist.h"


#define INFO_REF DeclarClientInfo *info = static_cast<DeclarClientInfo *>( p->p_dptr() );

DeclarClient::DeclarClient( DeclarClientList *parent ) :
    QObject(parent), DeclarClientInfo()
{
    p = new DeclarClient_P( this );
}

DeclarClient::DeclarClient( DeclarClientList *parent, const DeclarClientInfo &info ) :
    QObject(parent), DeclarClientInfo(info)
{
    p = new DeclarClient_P( this );
}

DeclarClient::DeclarClient( DeclarClientList *parent, DeclarClient *link ) :
    QObject(parent), DeclarClientInfo()
{
    p = new DeclarClient_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

DeclarClient::~DeclarClient()
{
    delete p;
    p = NULL;
}

DeclarClientList * DeclarClient::declarclientList() const
{
    return qobject_cast<DeclarClientList *>( parent() );
}

int DeclarClient::index() const
{
    DeclarClientList *pl = declarclientList();
    if ( pl == NULL ) return -1;

    return pl->declarclientIndex( p->p_dptr() );
}

QVariant DeclarClient::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void DeclarClient::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

QVariant DeclarClient::declarIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->declarIdentifier();
    return info->declarIdentifier();
}

void DeclarClient::setDeclarIdentifier( QVariant declarIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setDeclarIdentifier( declarIdentifier );
    else info->setDeclarIdentifier( declarIdentifier );
    emit declarIdentifierChanged();
}

QVariant DeclarClient::clientIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->clientIdentifier();
    return info->clientIdentifier();
}

void DeclarClient::setClientIdentifier( QVariant clientIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setClientIdentifier( clientIdentifier );
    else info->setClientIdentifier( clientIdentifier );
    emit clientIdentifierChanged();
}
