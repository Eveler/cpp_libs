#ifndef TREELISTITEMPRIVATE_H
#define TREELISTITEMPRIVATE_H

#include <QTreeWidgetItem>


class TreelistItem;

class TreelistItemPrivate
{
  friend class TreelistItem;
public:
  TreelistItemPrivate( TreelistItem *parent );

private:
  TreelistItem *m__Parent;

  QTreeWidgetItem *m__Item;
};

#endif // TREELISTITEMPRIVATE_H
