#include "treemodel.h"

#include "treeitem.h"


TreeModel::TreeModel(QObject * parent) :
  QObject(parent),
  m__Tree(QList<TreeItem *>()),
  m__Selected(QList<TreeItem *>()),
  m__ColumnCount(1)
{
}

TreeModel::~TreeModel()
{
  m__Selected.clear();
  while ( !m__Tree.isEmpty() )
  {
    TreeItem *item = m__Tree.takeFirst();
    disconnect( item, SIGNAL(selectedChanged(TreeItem*)),
                this, SLOT(treeItemSelectedChanged(TreeItem*)) );
    disconnect( item, SIGNAL(clicked(TreeItem*)),
                this, SIGNAL(treeItemClicked(TreeItem*)) );
    disconnect( item, SIGNAL(doubleClicked(TreeItem*)),
                this, SIGNAL(treeItemDoubleClicked(TreeItem*)) );
    disconnect( item, SIGNAL(destroyed(QObject*)),
                this, SLOT(treeItemDestroyed(QObject*)) );
    delete item;
    item = NULL;
  }
  m__ColumnCount = 0;
}

const QList<TreeItem *> & TreeModel::tree() const
{
  return m__Tree;
}

QList<QObject *> TreeModel::treeAsQObjects() const
{
  QList<QObject *> res;
  res.reserve(m__Tree.count());
  foreach ( TreeItem *i, m__Tree )
    res.append(i);
  return res;
}

const QList<TreeItem *> & TreeModel::selected() const
{
  return m__Selected;
}

QList<QObject *> TreeModel::selectedAsObjects() const
{
  QList<QObject *> res;
  res.reserve( m__Selected.count() );
  foreach ( TreeItem *i, m__Selected )
    res.append(i);
  return res;
}

void TreeModel::addTopLevelItem( TreeItem *item )
{
  if ( m__Tree.contains( item ) ) return;

  m__Tree << item;
  connect( item, SIGNAL(selectedChanged(TreeItem*)),
           this, SLOT(treeItemSelectedChanged(TreeItem*)) );
  connect( item, SIGNAL(clicked(TreeItem*)),
           this, SIGNAL(treeItemClicked(TreeItem*)) );
  connect( item, SIGNAL(doubleClicked(TreeItem*)),
           this, SIGNAL(treeItemDoubleClicked(TreeItem*)) );
  connect( item, SIGNAL(destroyed(QObject*)),
           this, SLOT(treeItemDestroyed(QObject*)) );
  emit treeChanged();
}

void TreeModel::removeTopLevelItem( TreeItem *item )
{
  disconnect( item, SIGNAL(selectedChanged(TreeItem*)),
              this, SLOT(treeItemSelectedChanged(TreeItem*)) );
  disconnect( item, SIGNAL(clicked(TreeItem*)),
              this, SIGNAL(treeItemClicked(TreeItem*)) );
  disconnect( item, SIGNAL(doubleClicked(TreeItem*)),
              this, SIGNAL(treeItemDoubleClicked(TreeItem*)) );
  disconnect( item, SIGNAL(destroyed(QObject*)),
              this, SLOT(treeItemDestroyed(QObject*)) );
  if ( !m__Tree.removeOne( item ) ) return;
  m__Selected.removeOne( item );

  emit treeChanged();
}

int TreeModel::columnCount() const
{
  return m__ColumnCount;
}

void TreeModel::setColumnCount( int columnCount )
{
  if ( columnCount < 0 ) columnCount = 0;

  m__ColumnCount = columnCount;
  emit columnCountChanged();
}

void TreeModel::treeItemSelectedChanged( TreeItem *treeItem )
{
  if ( !treeItem->isSelected() ) m__Selected.removeOne( treeItem );
  else if ( !m__Selected.contains( treeItem ) ) m__Selected << treeItem;
  emit selectedChanged( treeItem );
}

void TreeModel::treeItemDestroyed( QObject *obj )
{
  qDebug() << "treeItemDestroyed" << obj;
  TreeItem *item = (TreeItem *)obj;
  if ( m__Selected.removeOne( item ) )
    emit selectedChanged( NULL );

  if ( m__Tree.removeOne( item ) )
    emit treeChanged();
}
