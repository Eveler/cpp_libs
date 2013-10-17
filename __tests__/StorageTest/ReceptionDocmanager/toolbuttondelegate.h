#ifndef TOOLBUTTONDELEGATE_H
#define TOOLBUTTONDELEGATE_H

#include <QStyledItemDelegate>

class ToolButtonDelegate : public QStyledItemDelegate
{
public:
  ToolButtonDelegate(QObject *parent=0);
  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
  void setIcon(const QString text,const QIcon icon=QIcon());

private:
  QHash<QString, QIcon> m_Icon;

};

#endif // TOOLBUTTONDELEGATE_H
