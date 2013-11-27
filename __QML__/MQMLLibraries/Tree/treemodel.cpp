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

void TreeModel::addTopLevelItem( TreeItem *treeItem )
{
  if ( m__Tree.contains( treeItem ) ) return;

  m__Tree << treeItem;
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
