#include "destinationsstorage.h"

DestinationsStorage *DestinationsStorage::m__Instance = NULL;

DestinationsStorage * DestinationsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new DestinationsStorage;

  return m__Instance;
}

DestinationsStorage::DestinationsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

