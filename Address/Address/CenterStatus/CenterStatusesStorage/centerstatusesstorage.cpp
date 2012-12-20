#include "centerstatusesstorage.h"

CenterStatusesStorage *CenterStatusesStorage::m__Instance = NULL;

CenterStatusesStorage * CenterStatusesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new CenterStatusesStorage;

  return m__Instance;
}

CenterStatusesStorage::CenterStatusesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

