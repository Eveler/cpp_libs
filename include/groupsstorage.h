#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"
#include "group.h"

class GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT
public:
  static GroupsStorage * instance();

  const QList<AbstractSimpleObject *> & objects() const;

signals:

public slots:

private:
  static GroupsStorage *m__Instance;

  QList<AbstractSimpleObject *> m__Groups;

  explicit GroupsStorage(QObject *parent = 0);

  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
};

#endif // GROUPSSTORAGE_H
