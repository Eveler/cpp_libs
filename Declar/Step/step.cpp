#include "step.h"

Step::Step(QObject *parent) :
    QObject(parent)
{
  clear();
}

Step::~Step()
{
  clear();
}

const QVariant & Step::id() const
{
  return m__SS.m__Id;
}

const QList<Step *> & Step::prevSteps() const
{
  return m__SS.m__PrevSteps;
}

const QList<Step *> & Step::nextSteps() const
{
  return m__SS.m__NextSteps;
}

AbstractSimpleObject * Step::procedure() const
{
  return m__SS.m__Procedure;
}

AbstractSimpleObject * Step::destination() const
{
  return m__SS.m__Destination;
}

QDateTime Step::startDate() const
{
  return m__SS.m__StartDate;
}

QDate Step::controlDate() const
{
  return m__SS.m__ControlDate;
}

QDateTime Step::endDate() const
{
  return m__SS.m__EndDate;
}

User * Step::creator() const
{
  return m__SS.m__Creator;
}

const QString & Step::comment() const
{
  return m__SS.m__Comment;
}

const QString & Step::outnum() const
{
  return m__SS.m__Outnum;
}

QDateTime Step::outnumDate() const
{
  return m__SS.m__OutnumDate;
}

const QString & Step::innum() const
{
  return m__SS.m__Innum;
}

QDateTime Step::innumDate() const
{
  return m__SS.m__InnumDate;
}

User * Step::closer() const
{
  return m__SS.m__Closer;
}

Notification * Step::call() const
{
  return m__SS.m__Call;
}

Notification * Step::sms() const
{
  return m__SS.m__Sms;
}

const QList<Step *> & Step::noticeSteps() const
{
  return m__SS.m__NoticeSteps;
}

User * Step::agreed() const
{
  return m__SS.m__Agreed;
}

AbstractSimpleObject * Step::officeOwner() const
{
  return m__SS.m__OfficeOwner;
}

void Step::clear()
{
  m__SS.m__Id = QVariant();
  m__SS.m__PrevSteps = QList<Step *>();
  m__SS.m__NextSteps = QList<Step *>();
  m__SS.m__Procedure = NULL;
  m__SS.m__Destination = NULL;
  m__SS.m__StartDate = QDateTime();
  m__SS.m__ControlDate = QDate();
  m__SS.m__EndDate = QDateTime();
  m__SS.m__Creator = NULL;
  m__SS.m__Comment = QString();
  m__SS.m__Outnum = QString();
  m__SS.m__OutnumDate = QDateTime();
  m__SS.m__Innum = QString();
  m__SS.m__InnumDate = QDateTime();
  m__SS.m__Closer = NULL;
  m__SS.m__Call = NULL;
  m__SS.m__Sms = NULL;
  m__SS.m__NoticeSteps = QList<Step *>();
  m__SS.m__Agreed = NULL;
  m__SS.m__OfficeOwner = NULL;
}

void Step::setId( QVariant value )
{
  m__SS.m__Id = value;
}

bool Step::addPrevStep( Step *value )
{
  if ( m__SS.m__PrevSteps.contains( value ) || value == NULL )
    return false;

  m__SS.m__PrevSteps << value;

  return true;
}

bool Step::removePrevStep( Step *value )
{
  return m__SS.m__PrevSteps.removeOne( value );
}

bool Step::addNextStep( Step *value )
{
  if ( m__SS.m__NextSteps.contains( value ) || value == NULL )
    return false;

  m__SS.m__NextSteps << value;

  return true;
}

bool Step::removeNextStep( Step *value )
{
  return m__SS.m__NextSteps.removeOne( value );
}

void Step::setProcedure( AbstractSimpleObject *value )
{
  m__SS.m__Procedure = value;
}

void Step::setDestination( AbstractSimpleObject *value )
{
  m__SS.m__Destination = value;
}

void Step::setStartDate( QDateTime value )
{
  m__SS.m__StartDate = value;
}

void Step::setControlDate( QDate value )
{
  m__SS.m__ControlDate = value;
}

void Step::setEndDate( QDateTime value )
{
  m__SS.m__EndDate = value;
}

void Step::setCreator( User *value )
{
  m__SS.m__Creator = value;
}

void Step::setComment( QString value )
{
  m__SS.m__Comment = value;
}

void Step::setOutnum( QString value )
{
  m__SS.m__Outnum = value;
}

void Step::setOutnumDate( QDateTime value )
{
  m__SS.m__OutnumDate = value;
}

void Step::setInnum( QString value )
{
  m__SS.m__Innum = value;
}

void Step::setInnumDate( QDateTime value )
{
  m__SS.m__InnumDate = value;
}

void Step::setCloser( User *value )
{
  m__SS.m__Closer = value;
}

void Step::setCall( Notification *value )
{
  m__SS.m__Call = value;
}

void Step::setSms( Notification *value )
{
  m__SS.m__Sms = value;
}

bool Step::addNoticeStep( Step *value )
{
  if ( m__SS.m__NoticeSteps.contains( value ) || value == NULL )
    return false;

  m__SS.m__NoticeSteps << value;

  return true;
}

bool Step::removeNoticeStep( Step *value )
{
  return m__SS.m__NoticeSteps.removeOne( value );
}

void Step::setAgreed( User *value )
{
  m__SS.m__Agreed = value;
}

void Step::setOfficeOwner( AbstractSimpleObject *value )
{
  m__SS.m__OfficeOwner = value;
}

