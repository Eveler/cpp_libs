#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "amslogger.h"
#include "mreportdocument.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  MReportDocument *report = new MReportDocument(
        tr( "D:/devel/Libs/__tests__/MReportEngine/examples/report/config.xml" ), this );
  LogDebug() << report->fileName();
}

MainWindow::~MainWindow()
{
  delete ui;
}
