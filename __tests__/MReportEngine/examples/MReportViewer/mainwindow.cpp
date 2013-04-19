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
        tr( "D:/devel/Libs/__tests__/MReportEngine/examples/report/main.mrc" ), this );
  MReportDocument *errorDocument = report->errorDocument();
  if ( errorDocument != NULL )
    LogDebug() << report->lastError();
}

MainWindow::~MainWindow()
{
  delete ui;
}
