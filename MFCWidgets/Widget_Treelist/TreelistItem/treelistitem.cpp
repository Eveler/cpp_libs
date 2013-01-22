#include "treelistitem.h"

#include "treelistitemprivate.h"
#include "widget_treelist.h"

TreelistItem::TreelistItem( Widget_Treelist *parent ) :
  QObject(parent),
  m__Parent(parent),
  m__ParentItem(NULL),
  p(new TreelistItemPrivate( this ))
{
}

TreelistItem::TreelistItem( Widget_Treelist *parent, TreelistItem *parentItem ) :
  QObject(parent),
  m__Parent(parent),
  m__ParentItem(parentItem),
  p(new TreelistItemPrivate( this ))
{
}

Widget_Treelist * TreelistItem::parentList() const
{
  return m__Parent;
}

void TreelistItem::setLabel( int column, const QString &label )
{
  if ( column < 0 || column >= p->m__Item->columnCount() ) return;

  p->m__Item->setText( column, label );
}

void TreelistItem::setLabels( const QStringList &labels )
{
  if ( labels.count() != p->m__Item->columnCount() ) return;

  for ( int lIdx = 0; lIdx < labels.count(); lIdx++ )
    p->m__Item->setText( lIdx, labels[lIdx] );
}

void TreelistItem::addChild( TreelistItem *item )
{
  if ( m__ChildItems.contains( item ) ) return;

  item->m__ParentItem = this;
  m__ChildItems << item;
}

void TreelistItem::removeChild( TreelistItem *item )
{
  if ( !m__ChildItems.contains( item ) ) return;

  item->m__ParentItem = NULL;
  m__ChildItems.removeOne( item );
}

QTreeWidgetItem * TreelistItem::item() const
{
  return p->m__Item;
}
