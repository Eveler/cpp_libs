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
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_action_OpenReport_triggered()
{
  QString filePath = QFileDialog::getOpenFileName(
        this, tr( "Открыть файл отчета" ), QString(), tr( "Файлы MReport (*.mrf)" ) );
  if ( filePath.isEmpty() ) return;

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
        for ( int i = 0; i < 30; i++ )
        {
          date = date.addDays( 1 );
          dates << date;
        }
        parameter->setData( dates );
      }
  }

  QTime startTime;
  startTime.start();
  ui->wgt_ReportViewer->exec( reportDocument );
  delete reportDocument;
  reportDocument = NULL;
  ui->statusBar->showMessage( tr( "Отчет сформирова за %1мс." ).arg( startTime.elapsed() ), 5000 );
}
