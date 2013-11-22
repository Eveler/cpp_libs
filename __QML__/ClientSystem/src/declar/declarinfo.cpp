#include "declarinfo.h"


DeclarInfo::DeclarInfo() :
  m__Identifier(QVariant()),
  m__ServiceIdentifier(QVariant()),
  m__Number(0),
  m__CreateDate(QDateTime()),
  m__ControlDate(QDateTime()),
  m__RespiteDate(QDateTime()),
  m__CloseDate(QDateTime()),
  m__FirstLandmark(QString()),
  m__LastLandmark(QString()),
  m__DirectionIdentifier(QVariant()),
  m__ResponsibleIdentifier(QVariant()),
  m__OwnerIdentifier(QVariant()),
  m__Isnew(false),
  m__Deleted(false),
  m__ResultIdentifier(QVariant()),
  m__AssessmentTypeIdentifier(QVariant()),
  m__AssessmentIdentifier(QVariant()),
  m__ResultWayIdentifier(QVariant())
{
}

DeclarInfo::DeclarInfo( const DeclarInfo &other ) :
  m__Identifier(other.identifier()),
  m__ServiceIdentifier(other.serviceIdentifier()),
  m__Number(other.number()),
  m__CreateDate(other.createDate()),
  m__ControlDate(other.controlDate()),
  m__RespiteDate(other.respiteDate()),
  m__CloseDate(other.closeDate()),
  m__FirstLandmark(other.firstLandmark()),
  m__LastLandmark(other.lastLandmark()),
  m__DirectionIdentifier(other.directionIdentifier()),
  m__ResponsibleIdentifier(other.responsibleIdentifier()),
  m__OwnerIdentifier(other.ownerIdentifier()),
  m__Isnew(other.isnew()),
  m__Deleted(other.deleted()),
  m__ResultIdentifier(other.resultIdentifier()),
  m__AssessmentTypeIdentifier(other.assessmentTypeIdentifier()),
  m__AssessmentIdentifier(other.assessmentIdentifier()),
  m__ResultWayIdentifier(other.resultWayIdentifier())
{
}

DeclarInfo::~DeclarInfo()
{
}

QVariant DeclarInfo::identifier() const
{
  return m__Identifier;
}

void DeclarInfo::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
}

QVariant DeclarInfo::serviceIdentifier() const
{
  return m__ServiceIdentifier;
}

void DeclarInfo::setServiceIdentifier( QVariant serviceIdentifier )
{
  m__ServiceIdentifier = serviceIdentifier;
}

int DeclarInfo::number() const
{
  return m__Number;
}

void DeclarInfo::setNumber( int number )
{
  m__Number = number;
}

QDateTime DeclarInfo::createDate() const
{
  return m__CreateDate;
}

void DeclarInfo::setCreateDate( QDateTime createDate )
{
  m__CreateDate = createDate;
}

QDateTime DeclarInfo::controlDate() const
{
  return m__ControlDate;
}

void DeclarInfo::setControlDate( QDateTime controlDate )
{
  m__ControlDate = controlDate;
}

QDateTime DeclarInfo::respiteDate() const
{
  return m__RespiteDate;
}

void DeclarInfo::setRespiteDate( QDateTime respiteDate )
{
  m__RespiteDate = respiteDate;
}

QDateTime DeclarInfo::closeDate() const
{
  return m__CloseDate;
}

void DeclarInfo::setCloseDate( QDateTime closeDate )
{
  m__CloseDate = closeDate;
}

const QString & DeclarInfo::firstLandmark() const
{
  return m__FirstLandmark;
}

void DeclarInfo::setFirstLandmark( const QString &firstLandmark )
{
  m__FirstLandmark = firstLandmark;
}

const QString & DeclarInfo::lastLandmark() const
{
  return m__LastLandmark;
}

void DeclarInfo::setLastLandmark( const QString &lastLandmark )
{
  m__LastLandmark = lastLandmark;
}

QVariant DeclarInfo::directionIdentifier() const
{
  return m__DirectionIdentifier;
}

void DeclarInfo::setDirectionIdentifier( QVariant directionIdentifier )
{
  m__DirectionIdentifier = directionIdentifier;
}

QVariant DeclarInfo::responsibleIdentifier() const
{
  return m__ResponsibleIdentifier;
}

void DeclarInfo::setResponsibleIdentifier( QVariant responsibleIdentifier )
{
  m__ResponsibleIdentifier = responsibleIdentifier;
}

QVariant DeclarInfo::ownerIdentifier() const
{
  return m__OwnerIdentifier;
}

void DeclarInfo::setOwnerIdentifier( QVariant ownerIdentifier )
{
  m__OwnerIdentifier = ownerIdentifier;
}

bool DeclarInfo::isnew() const
{
  return m__Isnew;
}

void DeclarInfo::setIsnew( bool isnew )
{
  m__Isnew = isnew;
}

bool DeclarInfo::deleted() const
{
  return m__Deleted;
}

void DeclarInfo::setDeleted( bool deleted )
{
  m__Deleted = deleted;
}

QVariant DeclarInfo::resultIdentifier() const
{
  return m__ResultIdentifier;
}

void DeclarInfo::setResultIdentifier( QVariant resultIdentifier )
{
  m__ResultIdentifier = resultIdentifier;
}

QVariant DeclarInfo::assessmentTypeIdentifier() const
{
  return m__AssessmentTypeIdentifier;
}

void DeclarInfo::setAssessmentTypeIdentifier( QVariant assessmentTypeIdentifier )
{
  m__AssessmentTypeIdentifier = assessmentTypeIdentifier;
}

QVariant DeclarInfo::assessmentIdentifier() const
{
  return m__AssessmentIdentifier;
}

void DeclarInfo::setAssessmentIdentifier( QVariant assessmentIdentifier )
{
  m__AssessmentIdentifier = assessmentIdentifier;
}

QVariant DeclarInfo::resultWayIdentifier() const
{
  return m__ResultWayIdentifier;
}

void DeclarInfo::setResultWayIdentifier( QVariant resultWayIdentifier )
{
  m__ResultWayIdentifier = resultWayIdentifier;
}
