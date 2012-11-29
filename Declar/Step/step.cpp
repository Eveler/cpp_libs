#include "step.h"

#include "proceduresstorage.h"
#include "destinationsstorage.h"

Step::Step(QObject *parent) :
    QObject(parent)
{
  ProceduresStorage *ps = ProceduresStorage::instance();
  QList<AbstractSimpleObject *> procs = ps->objects();
}
