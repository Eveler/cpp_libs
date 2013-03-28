#ifndef GROUP_H
#define GROUP_H

#include "abstractsimpleobject.h"


class Group_P;
class GroupsStorage;

class EXPORT Group : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Group_P;
  friend class GroupsStorage;
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


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
