#ifndef DIRECTION_H
#define DIRECTION_H

#include "abstractsimpleobject.h"

#include "export/direction_export_lib.h"


class Direction;
class Direction_P;
class DirectionsStorage;
class Department;

typedef QList<Direction *> DirectionList;

class EXPORT_DIRECTION Direction : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Direction_P;
  friend class DirectionsStorage;


public:
  ~Direction();

  void setName( const QString &name );
  const QString & name() const;

  bool addChildDirection( Direction *childDirection );
  void removeChildDirection( Direction *childDirection );
  Direction * parentDirection() const;
  const DirectionList & childDirections() const;

  void setDepartment( Department *department );
  Department *department() const;


signals:
  void nameChanged();
  void childDirectionAdded( Direction *childDirection );
  void childDirectionRemoved( Direction *childDirection );
  void departmentChanged();


public slots:


private:
  Direction_P *p;

  explicit Direction( QVariant id, QObject *parent = 0 );
};

#endif // DIRECTION_H
