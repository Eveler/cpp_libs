#include "widget_recepriondocmanager.h"
#include "ui_widget_recepriondocmanager.h"

Widget_ReceprionDocmanager::Widget_ReceprionDocmanager(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_ReceprionDocmanager)
{
  ui->setupUi(this);
}

Widget_ReceprionDocmanager::~Widget_ReceprionDocmanager()
{
  delete ui;
}
