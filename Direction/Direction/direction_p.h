#ifndef DIRECTION_P_H
#define DIRECTION_P_H

#include <QObject>

#include "direction.h"


class Department;

class Direction_P : public QObject
{
  Q_OBJECT
  friend class Direction;


public:


signals:


public slots:


private:
  QString m__Name;
  Direction *m__ParentDirection;
  DirectionList m__ChildDirections;
  Department *m__Department;

  explicit Direction_P( Direction *parent = 0 );
  ~Direction_P();

  Direction * p_dptr() const;
  bool exists( Direction *search ) const;

  void setParentDirection( Direction *parentDirection );
  void setDepartment( Department *department );

private slots:
  void parentDirectionDestroyed();
  void childDirectionDestroyed( QObject *object );
  void departmentDestroyed();
};

#endif // DIRECTION_P_H
