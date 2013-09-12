#include "recipient.h"

#include "recipient_p.h"
#include "recipientlist.h"


#define INFO_REF RecipientInfo *info = static_cast<RecipientInfo *>( p->p_dptr() );

Recipient::Recipient( RecipientList *parent ) :
    QObject(parent), RecipientInfo()
{
    p = new Recipient_P( this );
}

Recipient::Recipient( RecipientList *parent, const RecipientInfo &info ) :
    QObject(parent), RecipientInfo(info)
{
    p = new Recipient_P( this );
}

Recipient::Recipient( RecipientList *parent, Recipient *link ) :
    QObject(parent), RecipientInfo()
{
    p = new Recipient_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Recipient::~Recipient()
{
    delete p;
    p = NULL;
}

RecipientList * Recipient::recipientList() const
{
    return qobject_cast<RecipientList *>( parent() );
}

int Recipient::index() const
{
    RecipientList *pl = recipientList();
    if ( pl == NULL ) return -1;

    return pl->recipientIndex( p->p_dptr() );
}

QVariant Recipient::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Recipient::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Recipient::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Recipient::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
