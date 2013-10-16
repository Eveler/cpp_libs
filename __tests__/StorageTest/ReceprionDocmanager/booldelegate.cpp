#include "booldelegate.h"
#include <QApplication>

BoolDelegate::BoolDelegate( QObject *parent ) :
  QStyledItemDelegate( parent )
{
  setIcon( true );
  setIcon( false );
  setText( true, QVariant( true ).toString() );
  setText( false, QVariant( false ).toString() );
}

void BoolDelegate::setIcon( bool value, QIcon icon )
{
  m_Icon[value] = icon;
}

void BoolDelegate::setText( bool value, QString text )
{
  m_Text[value] = text;
}

void BoolDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const{
  if(index.data().type()==QVariant::Bool){
    QStyleOptionButton buttonOption;
    buttonOption.rect = option.rect;
    buttonOption.features=QStyleOptionButton::Flat;
    buttonOption.icon=m_Icon[index.data().toBool()];
    buttonOption.iconSize.setHeight(option.rect.height()-3);
    buttonOption.iconSize.setWidth(option.rect.width()-3);
    buttonOption.state=QStyle::State_Enabled;
    buttonOption.text=m_Text[index.data().toBool()];
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel,
                                       &buttonOption, painter);
  } else
    QStyledItemDelegate::paint(painter, option, index);
}
