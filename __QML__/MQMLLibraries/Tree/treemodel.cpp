#include "treemodel.h"

#include "treeitem.h"


TreeModel::TreeModel(QObject * parent) :
  QObject(parent)
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
