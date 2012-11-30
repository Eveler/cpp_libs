#include "postsstorage.h"

PostsStorage *PostsStorage::m__Instance = NULL;

PostsStorage * PostsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new PostsStorage;

  return m__Instance;
}

const QList<AbstractSimpleObject *> & PostsStorage::objects() const
{
  return m__Posts;
}

PostsStorage::PostsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}

void PostsStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
}

void PostsStorage::recordAdded( MFCRecord *record, int index )
{
  Post *post = new Post( this );
  setObjectData( post, record );
  m__Posts.insert( index, post );
}

void PostsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  AbstractSimpleObject *obj = m__Posts.takeAt( index );
  delete obj;
}
