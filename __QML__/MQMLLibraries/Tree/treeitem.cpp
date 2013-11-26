#include "treeitem.h"

TreeItem::TreeItem( TreeItem * parent ) :
    QQuickItem(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  connect( this, SIGNAL(parentChanged(QQuickItem*)), SLOT(parentItemChanged(QQuickItem*)) );

  int nestingLevel = 0;
  if ( parent != NULL )
    nestingLevel = parent->nestingLevel()+1;
  m__NestingLevel = nestingLevel;
}

int TreeItem::nestingLevel() const
{
  return m__NestingLevel;
}

QVariant TreeItem::data( int column ) const
{
  if ( !m__Data.contains( column ) ) return QVariant();

  return m__Data[column];
}

void TreeItem::setData( QVariant data , int column )
{
  if ( column < 0 ) return;

  QVariant oldData = m__Data.value( column );
  m__Data[column] = data;
  if ( oldData != data || oldData.isNull() )
    emit dataChanged( column );
}

void TreeItem::parentItemChanged( QQuickItem *parent )
{
  int nestingLevel = 0;
  TreeItem *parentTreeItem = qobject_cast<TreeItem *>( parent );
  if ( parentTreeItem != NULL )
    nestingLevel = parentTreeItem->nestingLevel()+1;
  if ( nestingLevel != m__NestingLevel )
  {
    m__NestingLevel = nestingLevel;
    emit nestingLevelChanged();
  }
}
