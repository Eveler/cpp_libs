#include "postsstorage.h"

#include "post.h"


PostsStorage *PostsStorage::m__Instance = NULL;

PostsStorage * PostsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new PostsStorage;

  return m__Instance;
}

const PostList & PostsStorage::posts() const
{
  return *((PostList *)(&objects()));
}

AbstractSimpleObjectList PostsStorage::findByName(
    AbstractSimpleObjectList objects, QString name )
{
  AbstractSimpleObjectList result = AbstractSimpleObjectList();
  foreach ( AbstractSimpleObject *object, objects )
  {
    Post *post = qobject_cast<Post *>( object );
    if ( post->name() == name )
      result << object;
  }

  return result;
}

AbstractSimpleObject * PostsStorage::createObject( QVariant id )
{
  return new Post( id, this );
}

PostsStorage::PostsStorage(QObject *parent) :
    AbstractSimpleStorage(parent)
{
}
