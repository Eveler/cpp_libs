#include "postcodesstorage.h"

PostcodesStorage *PostcodesStorage::m__Instance = NULL;

PostcodesStorage * PostcodesStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new PostcodesStorage;

  return m__Instance;
}

PostcodesStorage::PostcodesStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

