#ifndef WIDGET_RECEPRIONDOCMANAGER_H
#define WIDGET_RECEPRIONDOCMANAGER_H

#include <QWidget>

namespace Ui {
  class Widget_ReceprionDocmanager;
}

class Widget_ReceprionDocmanager : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget_ReceprionDocmanager(QWidget *parent = 0);
    ~Widget_ReceprionDocmanager();

  private:
    Ui::Widget_ReceprionDocmanager *ui;
};

#endif // WIDGET_RECEPRIONDOCMANAGER_H
