#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "amslogger.h"
#include "mreportdocument.h"


MReportDocument *report;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  report = new MReportDocument(
        tr( "D:/devel/Libs/__tests__/MReportEngine/examples/report/main.mrc" ), this );
  MReportDocument *errorDocument = report->errorDocument();
  if ( errorDocument != NULL )
    LogDebug() << errorDocument->lastError();

  LogDebug() << report->exec();
}

MainWindow::~MainWindow()
{
  delete report;
  report = NULL;
  delete ui;
}
