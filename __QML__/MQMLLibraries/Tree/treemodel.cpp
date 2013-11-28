#include "treemodel.h"

#include "treeitem.h"


TreeModel::TreeModel(QObject * parent) :
  QObject(parent),
  m__Tree(QList<TreeItem *>()),
  m__ColumnCount(0)
{
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

void TreeModel::addTopLevelItem( TreeItem *treeItem )
{
  if ( m__Tree.contains( treeItem ) ) return;

  m__Tree << treeItem;
  connect( treeItem, SIGNAL(selectedChanged(TreeItem*)),
           this, SLOT(itemSelectedChanged(TreeItem*)) );
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

void TreeModel::itemSelectedChanged( TreeItem *item )
{
  if ( !item->selected() ) m__Selected.removeOne( item );
  else if ( !m__Selected.contains( item ) ) m__Selected << item;
  emit selectedChanged( item );
}
