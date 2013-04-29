#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "amslogger.h"
#include "mreportdocument.h"

#include <QDate>
#include <QFileDialog>
#include <QMessageBox>


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
}

MainWindow::~MainWindow()
{
  delete report;
  report = NULL;
  delete ui;
}

void MainWindow::on_action_OpenReport_triggered()
{
  QString filePath = QFileDialog::getOpenFileName(
        this, tr( "Открыть файл отчета" ), QString(), tr( "Файлы MReport (*.mrf)" ) );

  QString errorStr = QString();
  MReportDocument *reportDocument = MReportDocument::load( filePath, &errorStr, this );
  if ( reportDocument == NULL )
  {
    QMessageBox::warning( this, QString(), tr( "Ошибка загрузки файла отчета.\n%1" ).arg( errorStr ) );
    return;
  }
  MReportDocument *errorDocument = reportDocument->errorDocument();
  if ( errorDocument != NULL )
  {
    QMessageBox::warning( this, QString(), tr( "Ошибка в файле отчета.\n%1" ).arg(
                            errorDocument->lastError() ) );
    return;
  }

  if ( !reportDocument->reportSources().isEmpty() )
  {
    reportDocument->reportSources().first()->setUserName( tr( "postgres" ) );
    reportDocument->reportSources().first()->setPassword( tr( "me2db4con" ) );
  }
  if ( !reportDocument->reportParameters().isEmpty() )
  {
    foreach ( MReportParameter *parameter, reportDocument->reportParameters() )
      if ( parameter->parameterType() == MReportParameter::PT_InputData &&
           parameter->dataType() == MReportParameter::DT_DatePeriod )
      {
        QList<QVariant> dates = QList<QVariant>();
        QDate date( 2012, 12, 31 );
        for ( int i = 0; i < 7; i++ )
        {
          date = date.addDays( 1 );
          dates << date;
        }
        parameter->setData( dates );
      }
  }

  ui->wgt_ReportViewer->exec( reportDocument );
}
