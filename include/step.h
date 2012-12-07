#ifndef STEP_H
#define STEP_H

#include "user.h"
#include "notification.h"

#include <QDateTime>
#include <QVariant>

class Step : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QList<Step *> m__PrevSteps;
    QList<Step *> m__NextSteps;
    AbstractSimpleObject *m__Procedure;
    AbstractSimpleObject *m__Destination;
    QDateTime m__StartDate;
    QDate m__ControlDate;
    QDateTime m__EndDate;
    User *m__Creator;
    QString m__Comment;
    QString m__Outnum;
    QDateTime m__OutnumDate;
    QString m__Innum;
    QDateTime m__InnumDate;
    User *m__Closer;
    Notification *m__Call;
    Notification *m__Sms;
    QList<Step *> m__NoticeSteps;
    User *m__Agreed;
    AbstractSimpleObject *m__OfficeOwner;
  } StructStep;

  Q_OBJECT
public:
  explicit Step(QObject *parent = 0);
  ~Step();

  const QVariant & id() const;
  const QList<Step *> & prevSteps() const;
  const QList<Step *> & nextSteps() const;
  AbstractSimpleObject * procedure() const;
  AbstractSimpleObject * destination() const;
  QDateTime startDate() const;
  QDate controlDate() const;
  QDateTime endDate() const;
  User * creator() const;
  const QString & comment() const;
  const QString & outnum() const;
  QDateTime outnumDate() const;
  const QString & innum() const;
  QDateTime innumDate() const;
  User * closer() const;
  Notification * call() const;
  Notification * sms() const;
  const QList<Step *> & noticeSteps() const;
  User * agreed() const;
  AbstractSimpleObject * officeOwner() const;

signals:

public slots:
  void clear();

  void setId( QVariant value );
  bool addPrevStep( Step *value );
  bool removePrevStep( Step *value );
  bool addNextStep( Step *value );
  bool removeNextStep( Step *value );
  void setProcedure( AbstractSimpleObject *value );
  void setDestination( AbstractSimpleObject *value );
  void setStartDate( QDateTime value );
  void setControlDate( QDate value );
  void setEndDate( QDateTime value );
  void setCreator( User *value );
  void setComment( QString value );
  void setOutnum( QString value );
  void setOutnumDate( QDateTime value );
  void setInnum( QString value );
  void setInnumDate( QDateTime value );
  void setCloser( User *value );
  void setCall( Notification *value );
  void setSms( Notification *value );
  bool addNoticeStep( Step *value );
  bool removeNoticeStep( Step *value );
  void setAgreed( User *value );
  void setOfficeOwner( AbstractSimpleObject *value );

private:
  StructStep m__SS;
};

#endif // STEP_H
