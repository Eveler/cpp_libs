#include "mqml.h"

#include "Tree/treeitem.h"


MQML::MQML(QObject *parent) :
  QObject(parent)
{
}

TreeItem * MQML::createTreeItem( QVariant value ) const
{
  TreeItem *result = new TreeItem;
  result->setValue( value );
  return result;
}
