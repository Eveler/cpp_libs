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

  bool addRoot( QString fldVal = QString(), bool checkable = false, bool checked = false );
  bool addChild( QString rootVal, QString fldVal = QString(), bool checked = false );

  QStringList checkedItems();

  bool isEmpty();

signals:
  void checkStateChanged();

private:
  Ui::Widget_Treelist *ui;

  bool isAdding;
  bool isCheckChanging;

  QTreeWidget * treeWidget() const;

  QTreeWidgetItem *hasItem(QString val);
  QStringList checkedItems( QTreeWidgetItem *item );

private slots:
  void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

  void on_treeWidget_itemExpanded(QTreeWidgetItem *);
  void on_treeWidget_itemCollapsed(QTreeWidgetItem * item);
};

#endif // Widget_Treelist_H
