#ifndef TREELISTITEM_H
#define TREELISTITEM_H

#include <QObject>

#include "lib_export.h"


class TreelistItemPrivate;
class Widget_Treelist;
class QTreeWidgetItem;

class EXPORT TreelistItem : public QObject
{
  friend class TreelistItemPrivate;
  friend class Widget_Treelist;
public:
  explicit TreelistItem( Widget_Treelist *parent );
  explicit TreelistItem( Widget_Treelist *parent, TreelistItem *parentItem );

  Widget_Treelist * parentList() const;

  void setLabel( int column, const QString &label );
  void setLabels( const QStringList &labels );

  void addChild( TreelistItem *item );
  void removeChild( TreelistItem *item );
  const QList<TreelistItem *> childItems() const;

  TreelistItem * parentItem() const;

private:
  Widget_Treelist *m__Parent;
  TreelistItem *m__ParentItem;
  QList<TreelistItem *> m__ChildItems;

  TreelistItemPrivate *p;

  QTreeWidgetItem * item() const;
};

#endif // TREELISTITEM_H
