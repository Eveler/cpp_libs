#include "callsstorage.h"

CallsStorage *CallsStorage::m__Instance = NULL;

CallsStorage * CallsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new CallsStorage;

  return m__Instance;
}

CallsStorage::CallsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

