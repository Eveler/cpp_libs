#ifndef GROUP_H
#define GROUP_H

#include "abstractsimpleobject.h"

#include "export/group_export_lib.h"


class Group_P;
class GroupsStorage;

class EXPORT_GROUP Group : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Group_P;
  friend class GroupsStorage;


public:
  ~Group();

  void setName( const QString &name );
  const QString & name() const;


signals:
  void nameChanged();


public slots:


private:
  Group_P *p;

  explicit Group( QVariant id, QObject *parent = 0 );
};

#endif // GROUP_H
