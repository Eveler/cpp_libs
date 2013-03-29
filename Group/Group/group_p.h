#ifndef GROUP_P_H
#define GROUP_P_H

#include <QObject>

#include "group.h"


class Group_P : public QObject
{
  Q_OBJECT
  friend class Group;


public:


signals:


public slots:


private:
  QString m__Name;
  GroupList m__ParentGroups;
  GroupList m__ChildGroups;

  explicit Group_P( Group *parent = 0 );

  Group * p_dptr() const;
  bool exists( Group *search ) const;

private slots:
  void parentGroupDestroyed( QObject *object );
  void childGroupDestroyed( QObject *object );
};

#endif // GROUP_P_H
