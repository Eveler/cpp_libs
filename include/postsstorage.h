#ifndef POSTSSTORAGE_H
#define POSTSSTORAGE_H

#include "abstractsimplestorage.h"
#include "post.h"

class PostsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static PostsStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static PostsStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Posts;

  explicit PostsStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // POSTSSTORAGE_H
