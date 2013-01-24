#ifndef Widget_Treelist_H
#define Widget_Treelist_H

#include <QWidget>

#include "lib_export.h"


namespace Ui {
class Widget_Treelist;
}

class TreelistItem;
class TreelistItemPrivate;
class QTreeWidget;
class QTreeWidgetItem;

class EXPORT Widget_Treelist : public QWidget
{
  friend class TreelistItem;
  friend class TreelistItemPrivate;
  Q_OBJECT

public:
  explicit Widget_Treelist(QWidget *parent = 0);
  ~Widget_Treelist();

  QStringList columnNames() const;

  TreelistItem * addRoot( const QStringList &fldVal = QStringList(), bool checked = false );
  bool addRoot( TreelistItem *item );
  TreelistItem * addChild( TreelistItem *item, const QStringList &fldVal = QStringList(),
                           bool checked = false );
  bool removeItem( TreelistItem *item );

  const QList<TreelistItem *> & rootItems() const;

  QList<TreelistItem *> checkedItems();

  bool isEmpty();

  void resizeColumnToContents( int index );
  void resizeColumnsToContents();

  void setHeaderHidden( bool visible );

public slots:
  void checkAll( bool checked );

signals:
  void checkStateChanged();

private:
  Ui::Widget_Treelist *ui;

  bool isAdding;
  bool isCheckChanging;

  QList<TreelistItem *> m__RootItems;

  QTreeWidget * treeWidget() const;

private slots:
  void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);
  void on_tBt_CheckAll_clicked();
  void on_tBt_UncheckAll_clicked();
};

#endif // Widget_Treelist_H
