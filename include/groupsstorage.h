#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/group_export_lib.h"


class Group;

typedef QList<Group *> GroupList;

class EXPORT_GROUP GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static GroupsStorage * instance();

  const GroupList & groups() const;

  AbstractSimpleObjectList findByName( AbstractSimpleObjectList objects, QString name );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static GroupsStorage * m__Instance;

  explicit GroupsStorage(QObject *parent = 0);
};

#endif // GROUPSSTORAGE_H
