#include "officesstorage.h"

OfficesStorage *OfficesStorage::m__Instance = NULL;

OfficesStorage * OfficesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new OfficesStorage;

  return m__Instance;
}

OfficesStorage::OfficesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
