#ifndef GROUP_H
#define GROUP_H

#include "abstractsimpleobject.h"

#include "export/group_export_lib.h"


class Group;
class Group_P;
class GroupsStorage;

typedef QList<Group *> GroupList;

class EXPORT_GROUP Group : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Group_P;
  friend class GroupsStorage;


public:
  ~Group();

  void setName( const QString &name );
  const QString & name() const;

  bool addChildGroup( Group *childGroup );
  void removeChildGroup( Group *childGroup );
  const GroupList & parentGroups() const;
  const GroupList & childGroups() const;


signals:
  void nameChanged();
  void childGroupAdded( Group *childGroup );
  void childGroupRemoved( Group *childGroup );


public slots:


private:
  Group_P *p;

  explicit Group( QVariant id, QObject *parent = 0 );
};

#endif // GROUP_H
