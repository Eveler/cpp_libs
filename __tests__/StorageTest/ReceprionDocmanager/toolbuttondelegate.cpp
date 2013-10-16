#include "toolbuttondelegate.h"
#include <QApplication>

ToolButtonDelegate::ToolButtonDelegate(QObject *parent):
  QStyledItemDelegate(parent)
{
}

void ToolButtonDelegate::setIcon(const QString text, const QIcon icon){
  m_Icon[text]=icon;
}

void ToolButtonDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const{
  if(index.data().type()==QVariant::String &&
     !index.data().toString().isEmpty()){
    QStyleOptionButton button;
    button.rect = option.rect;
    button.icon=m_Icon.value(index.data().toString(),QIcon());
    button.iconSize.setHeight(option.rect.height()-3);
    button.iconSize.setWidth(option.rect.width()-3);
    button.features=QStyleOptionButton::DefaultButton;
//    button.text=index.data().toString();
    QApplication::style()->drawControl(
          QStyle::CE_PushButtonLabel,&button,painter);
  }else
    QStyledItemDelegate::paint(painter,option,index);
}
