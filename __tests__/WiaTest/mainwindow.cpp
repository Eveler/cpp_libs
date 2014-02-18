#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwia.h"
#include <QAxObject>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QAxObject *dialog = new QAxObject("WIA.CommonDialog");
  ui->textEdit->setHtml(dialog->generateDocumentation());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  QWia *wia = new QWia(this);
  wia->scan();
  delete wia;
}
