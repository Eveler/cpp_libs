#ifndef GROUP_H
#define GROUP_H

#include "abstractsimpleobject.h"

class Group : public AbstractSimpleObject
{
public:
  explicit Group(QObject *parent = 0);
};

#endif // GROUP_H
