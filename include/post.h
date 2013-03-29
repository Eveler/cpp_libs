#ifndef POST_H
#define POST_H

#include "abstractsimpleobject.h"

#include "export/post_export_lib.h"


class Post_P;
class PostsStorage;

class EXPORT_POST Post : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Post_P;
  friend class PostsStorage;


public:
  ~Post();

  void setName( const QString &name );
  const QString & name() const;


signals:
  void nameChanged();


public slots:


private:
  Post_P *p;

  explicit Post( QVariant id, QObject *parent = 0 );
};

#endif // POST_H
