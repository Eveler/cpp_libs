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
  explicit TreelistItem( Widget_Treelist *treeList );
  explicit TreelistItem( TreelistItem *parentItem );
  ~TreelistItem();

  Widget_Treelist * treeList() const;

  void setLabel( int column, const QString &label );
  void setLabels( const QStringList &labels );
  QString label( int column ) const;
  QStringList labels() const;

  void setChecked( bool checked );
  bool checked() const;

  QList<TreelistItem *> checkedChildItems() const;

  void addChild( TreelistItem *item );
  void removeChild( TreelistItem *item );
  const QList<TreelistItem *> childItems() const;

  TreelistItem * parentItem() const;

private:
  TreelistItemPrivate *m__P;

  QTreeWidgetItem * item() const;
  void removeFromTreelist();
};

#endif // TREELISTITEM_H
