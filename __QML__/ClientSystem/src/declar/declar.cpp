#include "declar.h"

#include "declar_p.h"
#include "declarlist.h"


#define INFO_REF DeclarInfo *info = static_cast<DeclarInfo *>( p->p_dptr() );

Declar::Declar( DeclarList *parent ) :
    QObject(parent), DeclarInfo()
{
    p = new Declar_P( this );
}

Declar::Declar( DeclarList *parent, const DeclarInfo &info ) :
    QObject(parent), DeclarInfo(info)
{
    p = new Declar_P( this );
}

Declar::Declar( DeclarList *parent, Declar *link ) :
    QObject(parent), DeclarInfo()
{
    p = new Declar_P( this );

    if ( parent == NULL ) return;

    p->m__Link = link;
}

Declar::~Declar()
{
    delete p;
    p = NULL;
}

DeclarList * Declar::declarList() const
{
    return qobject_cast<DeclarList *>( parent() );
}

int Declar::index() const
{
    DeclarList *pl = declarList();
    if ( pl == NULL ) return -1;

    return pl->declarIndex( p->p_dptr() );
}

QVariant Declar::identifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->identifier();
    return info->identifier();
}

void Declar::setIdentifier( QVariant identifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIdentifier( identifier );
    else info->setIdentifier( identifier );
    emit identifierChanged();
}

QVariant Declar::serviceIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->serviceIdentifier();
    return info->serviceIdentifier();
}

void Declar::setServiceIdentifier( QVariant serviceIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setServiceIdentifier( serviceIdentifier );
    else info->setServiceIdentifier( serviceIdentifier );
    emit serviceIdentifierChanged();
}

int Declar::number() const
{
    if ( parent() == NULL ) return 0;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->number();
    return info->number();
}

void Declar::setNumber( int number )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setNumber( number );
    else info->setNumber( number );
    emit numberChanged();
}

QDateTime Declar::createDate() const
{
    if ( parent() == NULL ) return QDateTime();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->createDate();
    return info->createDate();
}

void Declar::setCreateDate( QDateTime createDate )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setCreateDate( createDate );
    else info->setCreateDate( createDate );
    emit createDateChanged();
}

QDateTime Declar::controlDate() const
{
    if ( parent() == NULL ) return QDateTime();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->controlDate();
    return info->controlDate();
}

void Declar::setControlDate( QDateTime controlDate )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setControlDate( controlDate );
    else info->setControlDate( controlDate );
    emit controlDateChanged();
}

QDateTime Declar::respiteDate() const
{
    if ( parent() == NULL ) return QDateTime();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->respiteDate();
    return info->respiteDate();
}

void Declar::setRespiteDate( QDateTime respiteDate )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setRespiteDate( respiteDate );
    else info->setRespiteDate( respiteDate );
    emit respiteDateChanged();
}

QDateTime Declar::closeDate() const
{
    if ( parent() == NULL ) return QDateTime();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->closeDate();
    return info->closeDate();
}

void Declar::setCloseDate( QDateTime closeDate )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setCloseDate( closeDate );
    else info->setCloseDate( closeDate );
    emit closeDateChanged();
}

const QString & Declar::firstLandmark() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->firstLandmark();
    return info->firstLandmark();
}

void Declar::setFirstLandmark( const QString &firstLandmark )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setFirstLandmark( firstLandmark );
    else info->setFirstLandmark( firstLandmark );
    emit firstLandmarkChanged();
}

const QString & Declar::lastLandmark() const
{
    if ( parent() == NULL ) return p->m__NullString;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->lastLandmark();
    return info->lastLandmark();
}

void Declar::setLastLandmark( const QString &lastLandmark )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setLastLandmark( lastLandmark );
    else info->setLastLandmark( lastLandmark );
    emit lastLandmarkChanged();
}

QVariant Declar::directionIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->directionIdentifier();
    return info->directionIdentifier();
}

void Declar::setDirectionIdentifier( QVariant directionIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setDirectionIdentifier( directionIdentifier );
    else info->setDirectionIdentifier( directionIdentifier );
    emit directionIdentifierChanged();
}

QVariant Declar::responsibleIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->responsibleIdentifier();
    return info->responsibleIdentifier();
}

void Declar::setResponsibleIdentifier( QVariant responsibleIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setResponsibleIdentifier( responsibleIdentifier );
    else info->setResponsibleIdentifier( responsibleIdentifier );
    emit responsibleIdentifierChanged();
}

QVariant Declar::ownerIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->ownerIdentifier();
    return info->ownerIdentifier();
}

void Declar::setOwnerIdentifier( QVariant ownerIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setOwnerIdentifier( ownerIdentifier );
    else info->setOwnerIdentifier( ownerIdentifier );
    emit ownerIdentifierChanged();
}

bool Declar::isnew() const
{
    if ( parent() == NULL ) return false;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->isnew();
    return info->isnew();
}

void Declar::setIsnew( bool isnew )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setIsnew( isnew );
    else info->setIsnew( isnew );
    emit isnewChanged();
}

bool Declar::deleted() const
{
    if ( parent() == NULL ) return false;

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->deleted();
    return info->deleted();
}

void Declar::setDeleted( bool deleted )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setDeleted( deleted );
    else info->setDeleted( deleted );
    emit deletedChanged();
}

QVariant Declar::resultIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->resultIdentifier();
    return info->resultIdentifier();
}

void Declar::setResultIdentifier( QVariant resultIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setResultIdentifier( resultIdentifier );
    else info->setResultIdentifier( resultIdentifier );
    emit resultIdentifierChanged();
}

QVariant Declar::assessmentTypeIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->assessmentTypeIdentifier();
    return info->assessmentTypeIdentifier();
}

void Declar::setAssessmentTypeIdentifier( QVariant assessmentTypeIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setAssessmentTypeIdentifier( assessmentTypeIdentifier );
    else info->setAssessmentTypeIdentifier( assessmentTypeIdentifier );
    emit assessmentTypeIdentifierChanged();
}

QVariant Declar::assessmentIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->assessmentIdentifier();
    return info->assessmentIdentifier();
}

void Declar::setAssessmentIdentifier( QVariant assessmentIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setAssessmentIdentifier( assessmentIdentifier );
    else info->setAssessmentIdentifier( assessmentIdentifier );
    emit assessmentIdentifierChanged();
}

QVariant Declar::resultWayIdentifier() const
{
    if ( parent() == NULL ) return QVariant();

    INFO_REF;

    if ( p->m__Link != NULL ) return p->m__Link->resultWayIdentifier();
    return info->resultWayIdentifier();
}

void Declar::setResultWayIdentifier( QVariant resultWayIdentifier )
{
    if ( parent() == NULL ) return;

    INFO_REF;

    if ( p->m__Link != NULL ) p->m__Link->setResultWayIdentifier( resultWayIdentifier );
    else info->setResultWayIdentifier( resultWayIdentifier );
    emit resultWayIdentifierChanged();
}

