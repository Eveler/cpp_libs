#ifndef DECLAR_H
#define DECLAR_H

#include <QObject>

#include "step.h"
#include "service.h"

class Declar : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Service *m__Service;
    int m__Declarnum;
    QDateTime m__StartDate;
    QDate m__ControlDate;
    QDateTime m__EndDate;

  } DeclarStruct;

  Q_OBJECT
public:
  explicit Declar(QObject *parent = 0);

signals:

public slots:

};

#endif // DECLAR_H
