#include "proceduresstorage.h"

ProceduresStorage *ProceduresStorage::m__Instance = NULL;

ProceduresStorage * ProceduresStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new ProceduresStorage;

  return m__Instance;
}

ProceduresStorage::ProceduresStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

