#include "resultway.h"

#include "resultway_p.h"
#include "resultwaylist.h"


#define INFO_REF ResultwayInfo *info = static_cast<ResultwayInfo *>( p->p_dptr() );

Resultway::Resultway( ResultwayList *parent ) :
    QObject(parent), ResultwayInfo()
{
    p = new Resultway_P( this );
}

Resultway::Resultway( ResultwayList *parent, const ResultwayInfo &info ) :
    QObject(parent), ResultwayInfo(info)
{
    p = new Resultway_P( this );
}

Resultway::Resultway( ResultwayList *parent, Resultway *link ) :
    QObject(parent), ResultwayInfo()
{
    p = new Resultway_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Resultway::~Resultway()
{
    delete p;
    p = NULL;
}

ResultwayList * Resultway::resultwayList() const
{
    return qobject_cast<ResultwayList *>( parent() );
}

int Resultway::index() const
{
    ResultwayList *pl = resultwayList();
    if ( pl == NULL ) return -1;

    return pl->resultwayIndex( p->p_dptr() );
}

QVariant Resultway::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Resultway::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Resultway::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Resultway::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
