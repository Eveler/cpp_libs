#ifndef POSTSSTORAGE_H
#define POSTSSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/post_export_lib.h"


class Post;

typedef QList<Post *> PostList;

class EXPORT_POST PostsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static PostsStorage * instance();

  const PostList & posts() const;

  AbstractSimpleObjectList findByName( AbstractSimpleObjectList objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static PostsStorage *m__Instance;

  explicit PostsStorage(QObject *parent = 0);
};

#endif // POSTSSTORAGE_H
