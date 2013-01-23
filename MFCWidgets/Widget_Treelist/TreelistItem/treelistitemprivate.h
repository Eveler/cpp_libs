#ifndef TREELISTITEMPRIVATE_H
#define TREELISTITEMPRIVATE_H

#include <QTreeWidgetItem>


class TreelistItem;
class Widget_Treelist;

class TreelistItemPrivate
{
  friend class TreelistItem;
public:
  TreelistItemPrivate( TreelistItem *parent, Widget_Treelist *parentTreelist );
  TreelistItemPrivate( TreelistItem *parent, TreelistItem *parentItem );
  ~TreelistItemPrivate();

  void addChild( TreelistItem *item );
  void removeChild( TreelistItem *item );
  void setTreelist( Widget_Treelist *parentTreelist );
  void unsetTreelist();

private:
  TreelistItem *m__Parent;
  Widget_Treelist *m__ParentTreelist;
  TreelistItem *m__ParentItem;
  QList<TreelistItem *> m__ChildItems;
  int m__CheckedCount;

  QTreeWidgetItem *m__Item;
};

#endif // TREELISTITEMPRIVATE_H
