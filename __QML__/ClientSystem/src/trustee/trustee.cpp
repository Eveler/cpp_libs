#include "trustee.h"

#include "trustee_p.h"
#include "trusteelist.h"


#define INFO_REF TrusteeInfo *info = static_cast<TrusteeInfo *>( p->p_dptr() );

Trustee::Trustee( TrusteeList *parent ) :
    QObject(parent), TrusteeInfo()
{
    p = new Trustee_P( this );
}

Trustee::Trustee( TrusteeList *parent, const TrusteeInfo &info ) :
    QObject(parent), TrusteeInfo(info)
{
    p = new Trustee_P( this );
}

Trustee::Trustee( TrusteeList *parent, Trustee *link ) :
    QObject(parent), TrusteeInfo()
{
    p = new Trustee_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Trustee::~Trustee()
{
    delete p;
    p = NULL;
}

TrusteeList * Trustee::trusteeList() const
{
    return qobject_cast<TrusteeList *>( parent() );
}

int Trustee::index() const
{
    TrusteeList *pl = trusteeList();
    if ( pl == NULL ) return -1;

    return pl->trusteeIndex( p->p_dptr() );
}

QVariant Trustee::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Trustee::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

QVariant Trustee::declarIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->declarIdentifier();
    return info->declarIdentifier();
}

void Trustee::setDeclarIdentifier( QVariant declarIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setDeclarIdentifier( declarIdentifier );
    else info->setDeclarIdentifier( declarIdentifier );
    emit declarIdentifierChanged();
}

QVariant Trustee::trusteeClientIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->trusteeClientIdentifier();
    return info->trusteeClientIdentifier();
}

void Trustee::setTrusteeClientIdentifier( QVariant trusteeClientIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setTrusteeClientIdentifier( trusteeClientIdentifier );
    else info->setTrusteeClientIdentifier( trusteeClientIdentifier );
    emit trusteeClientIdentifierChanged();
}

QVariant Trustee::clientIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->clientIdentifier();
    return info->clientIdentifier();
}

void Trustee::setClientIdentifier( QVariant clientIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setClientIdentifier( clientIdentifier );
    else info->setClientIdentifier( clientIdentifier );
    emit clientIdentifierChanged();
}
