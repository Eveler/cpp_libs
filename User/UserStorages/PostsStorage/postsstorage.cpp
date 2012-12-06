#include "postsstorage.h"

PostsStorage *PostsStorage::m__Instance = NULL;

PostsStorage * PostsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new PostsStorage;

  return m__Instance;
}

PostsStorage::PostsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

