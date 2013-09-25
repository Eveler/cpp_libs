#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doclist_v2.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  if(!centralWidget()->layout())
    centralWidget()->setLayout(new QVBoxLayout(this));
  dl=new Doclist_v2(
        "192.168.91.60","mfctest","mike","me2db4con");
  centralWidget()->layout()->addWidget(dl);

  dl->addDeclar(148903);
  dl->allowEdit();
  dl->allowAdd();
  dl->allowRemove();
  dl->hideAdminControls(false);
}

MainWindow::~MainWindow()
{
  delete dl;
  delete ui;
}
