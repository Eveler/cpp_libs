#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mfcdocumentinfo.h"

#include "amslogger.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
