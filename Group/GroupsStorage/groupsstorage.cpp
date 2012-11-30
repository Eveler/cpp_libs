#include "groupsstorage.h"

GroupsStorage *GroupsStorage::m__Instance = NULL;

GroupsStorage * GroupsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new GroupsStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & GroupsStorage::objects() const
{
  return m__Groups;
}

GroupsStorage::GroupsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void GroupsStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
}

void GroupsStorage::recordAdded( MFCRecord *record, int index )
{
  Group *group = new Group( this );
  setObjectData( group, record );
  m__Groups.insert( index, group );
}

void GroupsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  AbstractSimpleObject *obj = m__Groups.takeAt( index );
  delete obj;
}
