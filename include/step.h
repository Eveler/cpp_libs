#ifndef STEP_H
#define STEP_H

#include "procedure.h"
#include "destination.h"

#include <QDateTime>
#include <QVariant>

class Step : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QList<Step *> m__Steps;
    Procedure *m__Procedure;
    Destination *m__Destination;
  } StructStep;

  Q_OBJECT
public:
  explicit Step(QObject *parent = 0);

  bool addPrevStep( Step *step );
  bool removePrevStep( Step *step );
  const QList<Step *> & prevSteps() const;

  bool setProcedure( Procedure *proc );
  Procedure * procedure() const;

  bool setDestination( Destination *dest );
  Destination * destination() const;

  void setStartDate( QDateTime value );
  QDateTime startDate() const;

  void setControlDate( QDate value );
  QDate controlDate() const;

  void setEndDate( QDateTime value );
  QDateTime endDate() const;

  void setComment( QString value );
  const QString & comment() const;



signals:

public slots:

private:
  StructStep m__SS;
};

#endif // STEP_H
