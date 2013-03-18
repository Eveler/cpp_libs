#include "treelistitemprivate.h"

#include "treelistitem.h"
#include "widget_treelist.h"

#include "amslogger.h"


TreelistItemPrivate::TreelistItemPrivate( TreelistItem *parent, Widget_Treelist *parentTreelist ) :
  m__Parent(parent),
  m__ParentTreelist(parentTreelist),
  m__ParentItem(NULL),
  m__ChildItems(QList<TreelistItem *>()),
  m__CheckedCount(0)
{
  m__Item = new QTreeWidgetItem( QStringList() << "" );
  m__ParentTreelist->treeWidget()->addTopLevelItem( m__Item );
}

TreelistItemPrivate::TreelistItemPrivate( TreelistItem *parent, TreelistItem *parentItem ) :
  m__Parent(parent),
  m__ParentTreelist(parentItem->treeList()),
  m__ParentItem(parentItem),
  m__ChildItems(QList<TreelistItem *>()),
  m__CheckedCount(0)
{
  m__Item = new QTreeWidgetItem( QStringList() << "" );

  m__ParentItem->m__P->m__ChildItems << m__Parent;
  m__ParentItem->m__P->m__Item->addChild( m__Item );

  if ( m__ParentItem->m__P->m__Item->checkState( 0 ) != Qt::Unchecked )
  {
    if ( m__ParentItem->m__P->m__CheckedCount > 0 )
      m__ParentItem->m__P->m__Item->setCheckState( 0, Qt::PartiallyChecked );
    else
      m__ParentItem->m__P->m__Item->setCheckState( 0, Qt::Unchecked );
  }
}

TreelistItemPrivate::~TreelistItemPrivate()
{
  m__Parent = NULL;
  m__ParentTreelist = NULL;
  m__ParentItem = NULL;
  m__CheckedCount = 0;

  while ( !m__ChildItems.isEmpty() )
  {
    TreelistItem *item = m__ChildItems.takeFirst();
    delete item;
    item = NULL;
  }
  delete m__Item;
}

void TreelistItemPrivate::addChild( TreelistItem *item )
{
  if ( m__ChildItems.contains( item ) ) return;

  if ( item->parentItem() != NULL && item->parentItem() != m__Parent )
    item->parentItem()->removeChild( item );
  else if ( item->treeList() != NULL && item->treeList() != m__ParentTreelist )
    item->removeFromTreelist();

  item->m__P->m__ParentItem = m__Parent;
  m__ChildItems << item;
  m__Item->addChild( item->item() );
  item->m__P->setTreelist( m__ParentTreelist );
}

void TreelistItemPrivate::removeChild( TreelistItem *item )
{
  if ( !m__ChildItems.contains( item ) ) return;

  item->m__P->m__ParentItem = NULL;
  m__ChildItems.removeOne( item );
  m__Item->removeChild( item->item() );
  item->m__P->unsetTreelist();
}

void TreelistItemPrivate::setTreelist( Widget_Treelist *parentTreelist )
{
  m__ParentTreelist = parentTreelist;
  foreach ( TreelistItem *item, m__ChildItems )
    item->m__P->setTreelist( m__ParentTreelist );
}

void TreelistItemPrivate::unsetTreelist()
{
  int index = m__ParentTreelist->treeWidget()->indexOfTopLevelItem( m__Item );
  if ( index > -1 )
    m__ParentTreelist->treeWidget()->takeTopLevelItem(
          m__ParentTreelist->treeWidget()->indexOfTopLevelItem( m__Item ) );
  foreach ( TreelistItem *item, m__ChildItems )
    item->m__P->unsetTreelist();
  m__ParentTreelist = NULL;
}
