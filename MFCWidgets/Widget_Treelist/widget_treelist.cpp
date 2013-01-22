#include "widget_treelist.h"
#include "ui_widget_treelist.h"

#include "treelistitem.h"


Widget_Treelist::Widget_Treelist(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_Treelist),
  isAdding(false),
  isCheckChanging(false)
{
  ui->setupUi(this);
}

Widget_Treelist::~Widget_Treelist()
{
  delete ui;
}

QStringList Widget_Treelist::columnNames() const
{
  QStringList result = QStringList();
  for ( int cIdx = 0; cIdx < ui->treeWidget->headerItem()->columnCount(); cIdx++ )
    result << ui->treeWidget->headerItem()->text( cIdx );
  return result;
}

bool Widget_Treelist::addRoot( QString fldVal, bool checkable, bool checked )
{
  if(fldVal.isEmpty() || hasItem(fldVal)!=0) return false;
  isAdding = true;
  ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList()<<"\n"<<fldVal));
  if ( checkable )
  {
    if ( checked )
      ui->treeWidget->topLevelItem(
            ui->treeWidget->topLevelItemCount()-1)->setCheckState( 0, Qt::Checked );
    else
      ui->treeWidget->topLevelItem(
            ui->treeWidget->topLevelItemCount()-1)->setCheckState( 0, Qt::Unchecked );
  }
  ui->treeWidget->resizeColumnToContents( 0 );
//  ui->treeWidget->resizeColumnToContents( 1 );
  isAdding = false;
  return true;
}

bool Widget_Treelist::addChild(QString rootVal, QString fldVal, bool checked ){
  if ( rootVal.isEmpty() || fldVal.isEmpty() ) return false;
  QTreeWidgetItem *item=hasItem(rootVal);
  if(item==0 || hasItem(fldVal)!=0) return false;
  isAdding = true;
  item->addChild(new QTreeWidgetItem(QStringList()<<""<<fldVal));
  if ( checked )
    item->child( item->childCount()-1 )->setCheckState( 0, Qt::Checked );
  else
    item->child( item->childCount()-1 )->setCheckState( 0, Qt::Unchecked );
  ui->treeWidget->resizeColumnToContents( 0 );
  ui->treeWidget->resizeColumnToContents( 1 );
  isAdding = false;
  return true;
}

QStringList Widget_Treelist::checkedItems()
{
  QStringList res = QStringList();

  for ( int iIdx = 0; iIdx < ui->treeWidget->topLevelItemCount(); iIdx++ )
  {
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem( iIdx );
    if ( item->childCount() > 0 ) res << checkedItems( item );
    else if ( item->checkState( 0 ) == Qt::Checked ) res << item->text( 1 );
  }

  return res;
}

bool Widget_Treelist::isEmpty()
{
  return (ui->treeWidget->topLevelItemCount() == 0);
}

QTreeWidget * Widget_Treelist::treeWidget() const
{
  return ui->treeWidget;
}

QTreeWidgetItem *Widget_Treelist::hasItem(QString val){
  QList< QTreeWidgetItem* > items=
      ui->treeWidget->findItems(val,Qt::MatchFixedString, 1);
  if(items.count()>0) return items.first();
  return 0;
}

QStringList Widget_Treelist::checkedItems( QTreeWidgetItem *item )
{
  QStringList res = QStringList();

  for ( int iIdx = 0; iIdx < item->childCount(); iIdx++ )
  {
    QTreeWidgetItem *sub_item = item->child( iIdx );
    if ( sub_item->childCount() > 0 ) res << checkedItems( sub_item );
    else if ( sub_item->checkState( 0 ) == Qt::Checked ) res << sub_item->text( 1 );
  }

  return res;
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

void Widget_Treelist::on_treeWidget_itemExpanded(QTreeWidgetItem */*item*/)
{
  ui->treeWidget->resizeColumnToContents( 0 );
}

void Widget_Treelist::on_treeWidget_itemCollapsed(QTreeWidgetItem *item)
{
  on_treeWidget_itemExpanded( item );
}
