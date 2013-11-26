#include "assessmenttype.h"

#include "assessmenttype_p.h"
#include "assessmenttypelist.h"


#define INFO_REF AssessmenttypeInfo *info = static_cast<AssessmenttypeInfo *>( p->p_dptr() );

Assessmenttype::Assessmenttype( AssessmenttypeList *parent ) :
    QObject(parent), AssessmenttypeInfo()
{
    p = new Assessmenttype_P( this );
}

Assessmenttype::Assessmenttype( AssessmenttypeList *parent, const AssessmenttypeInfo &info ) :
    QObject(parent), AssessmenttypeInfo(info)
{
    p = new Assessmenttype_P( this );
}

Assessmenttype::Assessmenttype( AssessmenttypeList *parent, Assessmenttype *link ) :
    QObject(parent), AssessmenttypeInfo()
{
    p = new Assessmenttype_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Assessmenttype::~Assessmenttype()
{
    delete p;
    p = NULL;
}

AssessmenttypeList * Assessmenttype::assessmenttypeList() const
{
    return qobject_cast<AssessmenttypeList *>( parent() );
}

int Assessmenttype::index() const
{
    AssessmenttypeList *pl = assessmenttypeList();
    if ( pl == NULL ) return -1;

    return pl->assessmenttypeIndex( p->p_dptr() );
}

QVariant Assessmenttype::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Assessmenttype::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Assessmenttype::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Assessmenttype::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
