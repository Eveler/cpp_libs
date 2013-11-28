#include "treeitem.h"

TreeItem::TreeItem( QQuickItem *parent ) :
  QQuickItem(parent),
  m__NestingLevel(0),
  m__Data(QHash<int, QVariant>()),
  m__Font(QHash<int, QFont>()),
  m__Selected(false),
  m__Opened(false),
  m__ParentItem(NULL),
  m__ChildItems(QList<TreeItem*>())
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);
}

int TreeItem::nestingLevel() const
{
  return m__NestingLevel;
}

QFont TreeItem::font() const
{
  if ( !m__Font.contains( 0 ) ) return QFont();

  return m__Font[0];
}

void TreeItem::setFont( const QFont &font )
{
  QFont oldFont = m__Font.value( 0 );
  m__Font[0] = font;
  if ( oldFont != font || oldFont == QFont() )
    emit fontChanged( 0 );
}

QVariant TreeItem::data() const
{
  if ( !m__Data.contains( 0 ) ) return QVariant();

  return m__Data[0];
}

void TreeItem::setData( QVariant data )
{
  QVariant oldData = m__Data.value( 0 );
  m__Data[0] = data;
  QFont f = font();
  f.setPixelSize( 14 );
  setFont( f );
  if ( oldData != data || oldData.isNull() )
    emit dataChanged( 0 );
}

QVariant TreeItem::columnData( int column ) const
{
  if ( !m__Data.contains( column ) ) return QVariant();

  return m__Data[column];
}

void TreeItem::setColumnData( QVariant data, int column )
{
  if ( column < 0 ) return;

  QVariant oldData = m__Data.value( column );
  m__Data[column] = data;
  if ( oldData != data || oldData.isNull() )
    emit dataChanged( column );
}

bool TreeItem::hasChild() const
{
    return !m__ChildItems.isEmpty();
}

bool TreeItem::selected() const
{
  return m__Selected;
}

void TreeItem::setSelected( bool selected )
{
  bool oldSelected = m__Selected;
  m__Selected = selected;
  if ( oldSelected != selected )
    emit selectedChanged( this );
}

bool TreeItem::childSelected() const
{
  return !m__SelectedItems.isEmpty();
}

bool TreeItem::opened() const
{
  return m__Opened;
}

void TreeItem::setOpened( bool opened )
{
  bool oldOpened = m__Opened;
  m__Opened = opened;
  if ( oldOpened != opened )
    emit openedChanged();
}

const QList<TreeItem *> &TreeItem::childItems() const
{
  return m__ChildItems;
}

const QList<QObject *> TreeItem::childItemsAsQObject() const
{
  QList<QObject *> res;
  res.reserve(m__ChildItems.count());
  foreach ( TreeItem *i, m__ChildItems )
    res << i;
  return res;
}

void TreeItem::addChildItem( TreeItem *childItem )
{
  if ( m__ChildItems.contains(childItem  ) ) return;

  m__ChildItems.append( childItem );
  childItem->setSelected( false );
  connect( childItem, SIGNAL(selectedChanged(TreeItem*)),
           this, SLOT(childSelected(TreeItem*)) );
  emit childItemsChanged();
  if( m__ChildItems.count() == 1 ) emit hasChildChanged();
  childItem->parentItemChanged( this );
}

void TreeItem::removeChildItem( TreeItem *childItem )
{
  if ( !m__ChildItems.removeOne( childItem ) ) return;

  disconnect( childItem, SIGNAL(selectedChanged(TreeItem*)),
              this, SLOT(childSelected(TreeItem*)) );
  childItem->setSelected( false );
  emit selectedChanged( childItem );
  if ( m__SelectedItems.removeOne( childItem ) && m__SelectedItems.isEmpty() )
    emit childSelectedChanged();
  emit childItemsChanged();
  if( m__ChildItems.count() == 0 ) emit hasChildChanged();
  childItem->parentItemChanged( NULL );
}

TreeItem * TreeItem::parentItem() const
{
  return m__ParentItem;
}

void TreeItem::parentItemChanged( TreeItem *parent )
{
  if ( m__ParentItem == parent ) return;

  int nestingLevel = 0;
  if ( m__ParentItem != NULL )
  {
    TreeItem *parentItem = m__ParentItem;
    m__ParentItem = NULL;
    parentItem->removeChildItem( this );
  }
  m__ParentItem = parent;
  if ( m__ParentItem != NULL )
    nestingLevel = m__ParentItem->nestingLevel()+1;
  if ( nestingLevel != m__NestingLevel )
  {
    m__NestingLevel = nestingLevel;
    emit nestingLevelChanged();
  }
}

void TreeItem::childSelected( TreeItem *item )
{
  if ( m__ChildItems.contains( item ) )
  {
    if ( item->selected() )
    {
      if ( !m__SelectedItems.contains( item ) )
      {
        m__SelectedItems << item;
        emit childSelectedChanged();
      }
    }
    else
    {
      m__SelectedItems.removeOne( item );
      emit childSelectedChanged();
    }
  }

  emit selectedChanged( item );
}
