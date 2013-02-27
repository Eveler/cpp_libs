#include "widget_treelist.h"
#include "ui_widget_treelist.h"

#include "treelistitem.h"

#if QT_VERSION >= 0x050000
#include "amslogger5.h"
#else
#include "amslogger.h"
#endif


Widget_Treelist::Widget_Treelist(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_Treelist),
  isAdding(false),
  isCheckChanging(false),
  m__RootItems(QList<TreelistItem *>())
{
  ui->setupUi(this);
}

Widget_Treelist::~Widget_Treelist()
{
  clear();
  delete ui;
}

QStringList Widget_Treelist::columnNames() const
{
  QStringList result = QStringList();
  for ( int cIdx = 0; cIdx < ui->treeWidget->headerItem()->columnCount(); cIdx++ )
    result << ui->treeWidget->headerItem()->text( cIdx );
  return result;
}

TreelistItem * Widget_Treelist::addRoot( const QStringList &fldVal, bool checked )
{
  isAdding = true;
  TreelistItem *newItem = new TreelistItem( this );
  newItem->setLabels( fldVal );
  newItem->setChecked( checked );
  m__RootItems << newItem;
//  ui->treeWidget->resizeColumnToContents( 0 );
  isAdding = false;

  return newItem;
}

bool Widget_Treelist::addRoot( TreelistItem *item )
{
  if ( item->treeList() == this ) return true;
  if ( item->treeList() != NULL )
  {

  }
}

TreelistItem * Widget_Treelist::addChild( TreelistItem *item, const QStringList &fldVal, bool checked )
{
  if ( item == NULL ) return NULL;

  isAdding = true;
  TreelistItem *newItem = new TreelistItem( item );
  newItem->setLabels( fldVal );
  newItem->setChecked( checked );
//  ui->treeWidget->resizeColumnToContents( 0 );
  isAdding = false;

  return newItem;
}

bool Widget_Treelist::removeItem( TreelistItem *item )
{
  if ( item == NULL || item->treeList() != this ) return false;

  if ( item->parentItem() == NULL ) item->removeFromTreelist();
  else item->parentItem()->removeChild( item );

  return true;
}

const QList<TreelistItem *> & Widget_Treelist::rootItems() const
{
  return m__RootItems;
}

QList<TreelistItem *> Widget_Treelist::checkedItems()
{
  QList<TreelistItem *> result = QList<TreelistItem *>();

  foreach ( TreelistItem *item, m__RootItems )
  {
    if ( item->checked() ) result << item;
    result << item->checkedChildItems();
  }

  return result;
}

bool Widget_Treelist::isEmpty()
{
  return (ui->treeWidget->topLevelItemCount() == 0);
}

void Widget_Treelist::resizeColumnToContents( int index )
{
  ui->treeWidget->resizeColumnToContents( index );
}

void Widget_Treelist::resizeColumnsToContents()
{
  ui->treeWidget->header()->resizeSections( QHeaderView::ResizeToContents );
}

void Widget_Treelist::setHeaderHidden( bool visible )
{
  ui->treeWidget->setHeaderHidden( visible );
}

void Widget_Treelist::clear()
{
  while ( !m__RootItems.isEmpty() )
  {
    TreelistItem *item = m__RootItems.takeFirst();
    delete item;
    item = NULL;
  }
}

void Widget_Treelist::checkAll( bool checked )
{
  foreach ( TreelistItem *item, m__RootItems ) item->setChecked( checked );
}

QTreeWidget * Widget_Treelist::treeWidget() const
{
  return ui->treeWidget;
}

void Widget_Treelist::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
  if ( column != 0 || isAdding ) return;

  if ( item->childCount() > 0 ){
    if( item->checkState(0)!=Qt::PartiallyChecked )
    {
      isCheckChanging=true;
      for(int i=0;i<item->childCount();i++)
        item->child(i)->setCheckState( 0, item->checkState(0));
      isCheckChanging=false;
    }
  }else{
    if ( !isCheckChanging )
    {
      QTreeWidgetItem* parent=item->parent();
      if(parent){
        int c=0;
        for(int i=0;i<parent->childCount();i++)
          if(parent->child(i)->checkState(0)==Qt::Checked) c++;
        if(c==0) parent->setCheckState(0,Qt::Unchecked);
        else if(c==parent->childCount()) parent->setCheckState(0,Qt::Checked);
        else parent->setCheckState(0,Qt::PartiallyChecked);
      }
    }
    emit checkStateChanged();
  }
}

void Widget_Treelist::on_tBt_CheckAll_clicked()
{
  checkAll( true );
}

void Widget_Treelist::on_tBt_UncheckAll_clicked()
{
  checkAll( false );
}
