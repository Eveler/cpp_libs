#include "procedure.h"

#include "procedure_p.h"
#include "procedurelist.h"


#define INFO_REF ProcedureInfo *info = static_cast<ProcedureInfo *>( p->p_dptr() );

Procedure::Procedure( ProcedureList *parent ) :
    QObject(parent), ProcedureInfo()
{
    p = new Procedure_P( this );
}

Procedure::Procedure( ProcedureList *parent, const ProcedureInfo &info ) :
    QObject(parent), ProcedureInfo(info)
{
    p = new Procedure_P( this );
}

Procedure::Procedure( ProcedureList *parent, Procedure *link ) :
    QObject(parent), ProcedureInfo()
{
    p = new Procedure_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Procedure::~Procedure()
{
    delete p;
    p = NULL;
}

ProcedureList * Procedure::procedureList() const
{
    return qobject_cast<ProcedureList *>( parent() );
}

int Procedure::index() const
{
    ProcedureList *pl = procedureList();
    if ( pl == NULL ) return -1;

    return pl->procedureIndex( p->p_dptr() );
}

QVariant Procedure::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Procedure::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Procedure::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Procedure::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
