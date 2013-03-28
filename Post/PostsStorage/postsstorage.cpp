#include "postsstorage.h"

#include "post.h"


PostsStorage *PostsStorage::m__Instance = NULL;

PostsStorage * PostsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new PostsStorage;

  return m__Instance;
}

QList<AbstractSimpleObject *> PostsStorage::findByName(
    QList<AbstractSimpleObject *> objects, QString name )
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();
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
