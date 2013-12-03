#include "treeitem.h"

#include <QDebug>


TreeItem::TreeItem( QObject *parent ) :
  QObject(parent),
  m__NestingLevel(0),
  m__Value(QHash<int, QVariant>()),
  m__Font(QHash<int, QFont>()),
  m__ItemEnabled(true),
  m__Selectable(true),
  m__Selected(false),
  m__Expandable(true),
  m__Expanded(false),
  m__ParentItem(NULL),
  m__ChildItems(QList<TreeItem*>())
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);
}

TreeItem::~TreeItem()
{
  m__ParentItem = NULL;
  m__SelectedItems.clear();
  while ( !m__ChildItems.isEmpty() )
  {
    TreeItem *item = m__ChildItems.takeFirst();
    disconnect( item, SIGNAL(selectedChanged(TreeItem*)),
                this, SLOT(childSelected(TreeItem*)) );
    disconnect( item, SIGNAL(clicked(TreeItem*)),
                this, SIGNAL(clicked(TreeItem*)) );
    disconnect( item, SIGNAL(doubleClicked(TreeItem*)),
                this, SIGNAL(doubleClicked(TreeItem*)) );
    disconnect( item, SIGNAL(destroyed(QObject*)),
                this, SLOT(childDestroyed(QObject*)) );
    delete item;
    item = NULL;
  }
}

int TreeItem::nestingLevel() const
{
  return m__NestingLevel;
}

QVariant TreeItem::propertyData( QString propertyName ) const
{
  return m__PropertyData.value( propertyName, QVariant() );
}

void TreeItem::setPropertyData( QString propertyName, QVariant data )
{
  QVariant oldData = propertyData( propertyName );
  m__PropertyData[propertyName] = data;
  if ( oldData != data ) emit propertyDataChanged( propertyName );
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

QVariant TreeItem::value() const
{
  if ( !m__Value.contains( 0 ) ) return QVariant();

  return m__Value[0];
}

void TreeItem::setValue( QVariant value )
{
  QVariant oldValue = m__Value.value( 0 );
  m__Value[0] = value;
  QFont f = font();
  f.setPixelSize( 14 );
  setFont( f );
  if ( oldValue != value || oldValue.isNull() )
    emit valueChanged( 0 );
}

QVariant TreeItem::columnValue( int column ) const
{
  if ( !m__Value.contains( column ) ) return QVariant();

  return m__Value[column];
}

void TreeItem::setColumnValue( QVariant value, int column )
{
  if ( column < 0 ) return;

  QVariant oldvalue = m__Value.value( column );
  m__Value[column] = value;
  if ( oldvalue != value || oldvalue.isNull() )
    emit valueChanged( column );
}

bool TreeItem::hasChild() const
{
    return !m__ChildItems.isEmpty();
}

bool TreeItem::itemEnabled() const
{
  bool parentEnabled = true;

  if ( m__ParentItem != NULL )
    parentEnabled = m__ParentItem->itemEnabled();

  if ( parentEnabled ) return m__ItemEnabled;
  else return parentEnabled;
}

void TreeItem::setItemEnabled( bool enabled )
{
  bool oldEnabled = m__ItemEnabled;
  m__ItemEnabled = enabled;
  if ( oldEnabled != enabled )
  {
    emit itemEnabledChanged();
    if ( m__Selected )
      emit selectedChanged( this );
  }
}

bool TreeItem::isSelectable() const
{
  return itemEnabled() && m__Selectable;
}

void TreeItem::setSelectable( bool selectable )
{
  bool oldSelectable = m__Selectable;
  m__Selectable = selectable;
  if ( oldSelectable != selectable )
  {
    emit selectableChanged();
    if ( m__Selected )
      emit selectedChanged( this );
  }
}

bool TreeItem::isSelected() const
{
  return isSelectable() && m__Selected;
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

bool TreeItem::isExpandable() const
{
  return hasChild() && m__Expandable;
}

void TreeItem::setExpandable( bool expandable )
{
  bool oldExpandable = m__Expandable;
  m__Expandable = expandable;
  if ( oldExpandable != expandable )
    emit expandableChanged();
}

bool TreeItem::isExpanded() const
{
  return m__Expanded;
}

void TreeItem::setExpanded( bool expanded )
{
  bool oldExpanded = m__Expanded;
  m__Expanded = expanded;
  if ( oldExpanded != expanded )
    emit expandedChanged();
}

const QList<TreeItem *> &TreeItem::childItems() const
{
  return m__ChildItems;
}

const QList<QObject *> TreeItem::childItemsAsQObject() const
{
  QList<QObject *> res;
  res.reserve(m__ChildItems.count());
  foreach ( TreeItem *item, m__ChildItems )
    res << item;
  return res;
}

void TreeItem::addChildItem( TreeItem *item )
{
  if ( m__ChildItems.contains( item ) ) return;

  int index = m__ChildItems.count();
  m__ChildItems.insert( index, item );
  item->setSelected( false );
  item->parentItemChanged( this );
  connect( item, SIGNAL(childItemsChanged()),
           this, SIGNAL(childItemsChanged()) );
  connect( item, SIGNAL(selectedChanged(TreeItem*)),
           this, SLOT(childSelected(TreeItem*)) );
  connect( item, SIGNAL(clicked(TreeItem*)),
           this, SIGNAL(clicked(TreeItem*)) );
  connect( item, SIGNAL(doubleClicked(TreeItem*)),
           this, SIGNAL(doubleClicked(TreeItem*)) );
  connect( item, SIGNAL(destroyed(QObject*)),
           this, SLOT(childDestroyed(QObject*)) );
  emit childItemAdded( index );
  emit childItemsChanged();
  if( m__ChildItems.count() == 1 )
  {
    emit hasChildChanged();
    emit expandableChanged();
  }
}

void TreeItem::removeChildItem( TreeItem *item )
{
  int index = m__ChildItems.indexOf( item );
  if ( index < 0 ) return;

  disconnect( item, SIGNAL(childItemsChanged()),
              this, SIGNAL(childItemsChanged()) );
  disconnect( item, SIGNAL(selectedChanged(TreeItem*)),
              this, SLOT(childSelected(TreeItem*)) );
  disconnect( item, SIGNAL(clicked(TreeItem*)),
              this, SIGNAL(clicked(TreeItem*)) );
  disconnect( item, SIGNAL(doubleClicked(TreeItem*)),
              this, SIGNAL(doubleClicked(TreeItem*)) );
  disconnect( item, SIGNAL(destroyed(QObject*)),
              this, SLOT(childDestroyed(QObject*)) );
  item->setSelected( false );
  item->parentItemChanged( NULL );
  m__ChildItems.removeAt( index );
  emit selectedChanged( item );
  if ( m__SelectedItems.removeOne( item ) && m__SelectedItems.isEmpty() )
    emit childSelectedChanged();
  emit childItemRemoved( index );
  emit childItemsChanged();
  if( m__ChildItems.isEmpty() )
  {
    emit hasChildChanged();
    emit expandableChanged();
  }
}

TreeItem * TreeItem::parentItem() const
{
  return m__ParentItem;
}

void TreeItem::click()
{
  emit clicked( this );
}

void TreeItem::doubleClick()
{
  emit doubleClicked( this );
}

void TreeItem::parentItemChanged( TreeItem *parent )
{
  if ( m__ParentItem == parent ) return;

  int nestingLevel = 0;
  if ( m__ParentItem != NULL )
  {
    disconnect( m__ParentItem, SIGNAL(itemEnabledChanged()),
                this, SLOT(parentEnabledChanged()) );
    TreeItem *parentItem = m__ParentItem;
    m__ParentItem = NULL;
    parentItem->removeChildItem( this );
  }
  m__ParentItem = parent;
  if ( m__ParentItem != NULL )
  {
    connect( m__ParentItem, SIGNAL(itemEnabledChanged()),
             this, SLOT(parentEnabledChanged()) );
    nestingLevel = m__ParentItem->nestingLevel()+1;
  }
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
    if ( item->isSelected() )
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

void TreeItem::childDestroyed( QObject *obj )
{
  TreeItem *item = (TreeItem *)obj;
  if ( m__SelectedItems.removeOne( item ) )
    emit childSelectedChanged();

  int index = m__ChildItems.indexOf( item );
  if ( index < 0 ) return;

  m__ChildItems.removeAt( index );
  emit childItemRemoved( index );
  emit childItemsChanged();
  if ( m__ChildItems.isEmpty() )
  {
    emit hasChildChanged();
    emit expandableChanged();
  }

  emit destroyed( obj );
}

void TreeItem::parentEnabledChanged()
{
  emit itemEnabledChanged();
  emit selectedChanged( this );
}
