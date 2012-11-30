#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "abstractsimpleobject.h"

class Department : public AbstractSimpleObject
{
  Q_OBJECT
public:
  explicit Department(QObject *parent = 0);

signals:

public slots:

};

#endif // DEPARTMENT_H
