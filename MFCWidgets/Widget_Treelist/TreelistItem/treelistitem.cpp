#include "treelistitem.h"

#include "treelistitemprivate.h"
#include "widget_treelist.h"

#include "amslogger5.h"

TreelistItem::TreelistItem( Widget_Treelist *treeList ) :
  QObject(treeList),
  m__P(new TreelistItemPrivate( this, treeList ))
{
}

TreelistItem::TreelistItem( TreelistItem *parentItem ) :
  QObject(parentItem->treeList()),
  m__P(new TreelistItemPrivate( this, parentItem ))
{
}

TreelistItem::~TreelistItem()
{
  delete m__P;
}

Widget_Treelist * TreelistItem::treeList() const
{
  return m__P->m__ParentTreelist;
}

void TreelistItem::setLabel( int column, const QString &label )
{
  m__P->m__Item->setText( column+0, label );
}

void TreelistItem::setLabels( const QStringList &labels )
{
  for ( int lIdx = 0; lIdx < labels.count(); lIdx++ )
    setLabel( lIdx, labels[lIdx] );
}

QString TreelistItem::label( int column ) const
{
  return m__P->m__Item->text( column );
}

QStringList TreelistItem::labels() const
{
  QStringList result = QStringList();
  for ( int lIdx = 0; lIdx < m__P->m__Item->columnCount(); lIdx++ )
    result << m__P->m__Item->text( lIdx );
  return result;
}

void TreelistItem::setChecked( bool checked )
{
  if ( checked )
  {
    if ( parentItem() != NULL && m__P->m__Item->checkState( 0 ) != Qt::Checked )
      parentItem()->m__P->m__CheckedCount++;
    m__P->m__Item->setCheckState( 0, Qt::Checked );
  }
  else if ( !checked )
  {
    if ( parentItem() != NULL && m__P->m__Item->checkState( 0 ) != Qt::Unchecked )
      parentItem()->m__P->m__CheckedCount--;
    m__P->m__Item->setCheckState( 0, Qt::Unchecked );
  }
}

bool TreelistItem::checked() const
{
  return ( m__P->m__Item->checkState( 0 ) != Qt::Unchecked );
}

QList<TreelistItem *> TreelistItem::checkedChildItems() const
{
  QList<TreelistItem *> result = QList<TreelistItem *>();

  foreach ( TreelistItem *item, m__P->m__ChildItems )
  {
    if ( item->checked() ) result << item;
    result << item->checkedChildItems();
  }

  return result;
}

void TreelistItem::addChild( TreelistItem *item )
{
  m__P->addChild( item );
}

void TreelistItem::removeChild( TreelistItem *item )
{
  m__P->removeChild( item );
}

const QList<TreelistItem *> TreelistItem::childItems() const
{
  return m__P->m__ChildItems;
}

TreelistItem * TreelistItem::parentItem() const
{
  return m__P->m__ParentItem;
}

QTreeWidgetItem * TreelistItem::item() const
{
  return m__P->m__Item;
}

void TreelistItem::removeFromTreelist()
{
  m__P->unsetTreelist();
}
