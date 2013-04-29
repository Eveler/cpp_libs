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

//  report = new MReportDocument(
//        tr( "D:/devel/Libs/__tests__/MReportEngine/examples/report/main.mrc" ), this );
//  MReportDocument *errorDocument = report->errorDocument();
//  if ( errorDocument != NULL )
//    LogDebug() << errorDocument->lastError();

//  if ( !report->reportSources().isEmpty() )
//  {
////    LogDebug() << report->reportSources().first()->isValid();
//    report->reportSources().first()->setUserName( tr( "postgres" ) );
//    report->reportSources().first()->setPassword( tr( "me2db4con" ) );
////    LogDebug() << report->reportSources().first()->executeQuery(
////                    tr( "SELECT now()" ) );
////    for ( int i = 0; i < 1000; i++ )
////      report->reportSources().first()->executeQuery( tr( "SELECT now()" ) );
////    LogDebug() << report->reportSources().first()->executeQuery(
////                    tr( "SELECT now()" ) );
//  }
//  if ( !report->reportParameters().isEmpty() )
//  {
//    foreach ( MReportParameter *parameter, report->reportParameters() )
//      if ( parameter->parameterType() == MReportParameter::PT_InputData &&
//           parameter->dataType() == MReportParameter::DT_DatePeriod )
//      {
//        QList<QVariant> dates = QList<QVariant>();
//        QDate date( 2012, 12, 31 );
////        LogDebug() << tr( "TYT" );
//        for ( int i = 0; i < 7; i++ )
//        {
//          date = date.addDays( 1 );
//          dates << date;
//        }
////        LogDebug() << tr( "TYT" );
//        parameter->setData( dates );
//      }
//  }
//  LogDebug() << report->exec();
////  report->exec();

  MReportDocument *report = MReportDocument::load( tr( "D:/report.mrf" ), this );
  LogDebug() << report;
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
        QDate date( 2012, 12, 31 );
        //        LogDebug() << tr( "TYT" );
        for ( int i = 0; i < 7; i++ )
        {
          date = date.addDays( 1 );
          dates << date;
        }
        //        LogDebug() << tr( "TYT" );
        parameter->setData( dates );
      }
  }
  LogDebug() << report->exec();
}

MainWindow::~MainWindow()
{
  delete report;
  report = NULL;
  delete ui;
}
