#ifndef BOOLDELEGATE_H
#define BOOLDELEGATE_H

#include <QStyledItemDelegate>
#include <QHash>
#include <QIcon>
#include <QString>

class BoolDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit BoolDelegate( QObject *parent = 0 );

  void setIcon( bool value, QIcon icon = QIcon() );
  void setText( bool value, QString text = QString() );

  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;

signals:

public slots:

private:
  QHash<bool, QIcon> m_Icon;
  QHash<bool, QString> m_Text;
};

#endif // BOOLDELEGATE_H
