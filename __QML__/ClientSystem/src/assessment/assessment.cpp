#include "assessment.h"

#include "assessment_p.h"
#include "assessmentlist.h"


#define INFO_REF AssessmentInfo *info = static_cast<AssessmentInfo *>( p->p_dptr() );

Assessment::Assessment( AssessmentList *parent ) :
    QObject(parent), AssessmentInfo()
{
    p = new Assessment_P( this );
}

Assessment::Assessment( AssessmentList *parent, const AssessmentInfo &info ) :
    QObject(parent), AssessmentInfo(info)
{
    p = new Assessment_P( this );
}

Assessment::Assessment( AssessmentList *parent, Assessment *link ) :
    QObject(parent), AssessmentInfo()
{
    p = new Assessment_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Assessment::~Assessment()
{
    delete p;
    p = NULL;
}

AssessmentList * Assessment::assessmentList() const
{
    return qobject_cast<AssessmentList *>( parent() );
}

int Assessment::index() const
{
    AssessmentList *pl = assessmentList();
    if ( pl == NULL ) return -1;

    return pl->assessmentIndex( p->p_dptr() );
}

QVariant Assessment::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Assessment::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

const QString & Assessment::name() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->name();
    return info->name();
}

void Assessment::setName( const QString &name )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setName( name );
    else info->setName( name );
    emit nameChanged();
}
