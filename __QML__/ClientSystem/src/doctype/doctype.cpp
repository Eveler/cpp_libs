#include "doctype.h"

#include "doctype_p.h"
#include "doctypelist.h"


#define INFO_REF DoctypeInfo *info = static_cast<DoctypeInfo *>( p->p_dptr() );

Doctype::Doctype( DoctypeList *parent ) :
    QObject(parent), DoctypeInfo()
{
    p = new Doctype_P( this );
}

Doctype::Doctype( DoctypeList *parent, const DoctypeInfo &info ) :
    QObject(parent), DoctypeInfo(info)
{
    p = new Doctype_P( this );
}

Doctype::Doctype( DoctypeList *parent, Doctype *link ) :
    QObject(parent), DoctypeInfo()
{
    p = new Doctype_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Doctype::~Doctype()
{
    delete p;
    p = NULL;
}

DoctypeList * Doctype::doctypeList() const
{
    return qobject_cast<DoctypeList *>( parent() );
}

int Doctype::index() const
{
    DoctypeList *pl = doctypeList();
    if ( pl == NULL ) return -1;

    return pl->doctypeIndex( p->p_dptr() );
}

QVariant Doctype::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Doctype::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Doctype::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Doctype::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
