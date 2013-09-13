#include "callstatus.h"

#include "callstatus_p.h"
#include "callstatuslist.h"


#define INFO_REF CallstatusInfo *info = static_cast<CallstatusInfo *>( p->p_dptr() );

Callstatus::Callstatus( CallstatusList *parent ) :
    QObject(parent), CallstatusInfo()
{
    p = new Callstatus_P( this );
}

Callstatus::Callstatus( CallstatusList *parent, const CallstatusInfo &info ) :
    QObject(parent), CallstatusInfo(info)
{
    p = new Callstatus_P( this );
}

Callstatus::Callstatus( CallstatusList *parent, Callstatus *link ) :
    QObject(parent), CallstatusInfo()
{
    p = new Callstatus_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Callstatus::~Callstatus()
{
    delete p;
    p = NULL;
}

CallstatusList * Callstatus::callstatusList() const
{
    return qobject_cast<CallstatusList *>( parent() );
}

int Callstatus::index() const
{
    CallstatusList *pl = callstatusList();
    if ( pl == NULL ) return -1;

    return pl->callstatusIndex( p->p_dptr() );
}

QVariant Callstatus::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Callstatus::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Callstatus::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Callstatus::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
