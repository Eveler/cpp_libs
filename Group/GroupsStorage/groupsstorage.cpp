#include "groupsstorage.h"

GroupsStorage *GroupsStorage::m__Instance = NULL;

GroupsStorage * GroupsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new GroupsStorage;

  return m__Instance;
}

GroupsStorage::GroupsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
