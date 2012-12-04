#ifndef STEP_H
#define STEP_H

#include "user.h"

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
  } StructStep;

  Q_OBJECT
public:
  explicit Step(QObject *parent = 0);

  bool addPrevStep( Step *value );
  bool removePrevStep( Step *value );
  const QList<Step *> & prevSteps() const;

  bool addNextStep( Step *value );
  bool removeNextStep( Step *value );
  const QList<Step *> & nextSteps() const;

  bool setProcedure( AbstractSimpleObject *value );
  Procedure * procedure() const;

  bool setDestination( AbstractSimpleObject *value );
  Destination * destination() const;

  void setStartDate( QDateTime value );
  QDateTime startDate() const;

  void setControlDate( QDate value );
  QDate controlDate() const;

  void setEndDate( QDateTime value );
  QDateTime endDate() const;

  void setCreator( User *value );
  User *creator() const;

  void setComment( QString value );
  const QString & comment() const;

  void setOutnum( QString value );
  const QString & outnum() const;

  void setOutnumDate( QDateTime value );
  QDateTime outnumDate() const;

  void setInnum( QString value );
  const QString & innum() const;

  void setInnumDate( QDateTime value );
  QDateTime innumDate() const;

  void setCloser( User *value );
  User *closer() const;

signals:

public slots:

private:
  StructStep m__SS;
};

#endif // STEP_H
