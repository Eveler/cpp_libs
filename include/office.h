#ifndef OFFICE_H
#define OFFICE_H

#include "abstractsimpleobject.h"

class Office : public AbstractSimpleObject
{
public:
  explicit Office(QObject *parent = 0);
};

#endif // OFFICE_H
