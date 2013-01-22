#include "treelistitemprivate.h"

#include "treelistitem.h"
#include "widget_treelist.h"

TreelistItemPrivate::TreelistItemPrivate( TreelistItem *parent ) :
  m__Parent( parent )
{
  m__Item = new QTreeWidgetItem();
  if ( m__Parent->m__ParentItem == NULL )
    m__Parent->parentList()->treeWidget()->addTopLevelItem( m__Item );
  else
  {
    m__Parent->m__ParentItem->p->m__Item->addChild( m__Item );
  }
}
