#include "result.h"

#include "result_p.h"
#include "resultlist.h"


#define INFO_REF ResultInfo *info = static_cast<ResultInfo *>( p->p_dptr() );

Result::Result( ResultList *parent ) :
    QObject(parent), ResultInfo()
{
    p = new Result_P( this );
}

Result::Result( ResultList *parent, const ResultInfo &info ) :
    QObject(parent), ResultInfo(info)
{
    p = new Result_P( this );
}

Result::Result( ResultList *parent, Result *link ) :
    QObject(parent), ResultInfo()
{
    p = new Result_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Result::~Result()
{
    delete p;
    p = NULL;
}

ResultList * Result::resultList() const
{
    return qobject_cast<ResultList *>( parent() );
}

int Result::index() const
{
    ResultList *pl = resultList();
    if ( pl == NULL ) return -1;

    return pl->resultIndex( p->p_dptr() );
}

QVariant Result::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Result::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Result::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Result::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
