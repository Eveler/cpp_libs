#ifndef POST_H
#define POST_H

#include "abstractsimpleobject.h"


class Post_P;
class PostsStorage;

class EXPORT Post : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Post_P;
  friend class PostsStorage;
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


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
