#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "amslogger.h"
#include "mreportdocument.h"

#include <QDate>


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

  if ( !report->reportSources().isEmpty() )
  {
//    LogDebug() << report->reportSources().first()->isValid();
    report->reportSources().first()->setUserName( tr( "postgres" ) );
    report->reportSources().first()->setPassword( tr( "me2db4con" ) );
//    LogDebug() << report->reportSources().first()->executeQuery(
//                    tr( "SELECT now()" ) );
//    for ( int i = 0; i < 1000; i++ )
//      report->reportSources().first()->executeQuery( tr( "SELECT now()" ) );
//    LogDebug() << report->reportSources().first()->executeQuery(
//                    tr( "SELECT now()" ) );
  }
  if ( !report->reportParameters().isEmpty() )
  {
    foreach ( MReportParameter *parameter, report->reportParameters() )
      if ( parameter->parameterType() == MReportParameter::PT_InputData &&
           parameter->dataType() == MReportParameter::DT_DatePeriod )
      {
        QList<QVariant> dates = QList<QVariant>();
        dates << QDate( 2013, 4, 15 );
        dates << QDate( 2013, 4, 16 );
        dates << QDate( 2013, 4, 17 );
        dates << QDate( 2013, 4, 18 );
        dates << QDate( 2013, 4, 19 );
        dates << QDate( 2013, 4, 20 );
        parameter->setData( dates );
      }
  }
  LogDebug() << report->exec();
//  report->exec();
}

MainWindow::~MainWindow()
{
  delete report;
  report = NULL;
  delete ui;
}
