#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "amslogger.h"
#include "mreportdocument.h"

#include <QDate>
#include <QFileDialog>
#include <QMessageBox>

#include <QDomDocument>


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
    MReportParameterList parameters = reportDocument->reportParameters();
    parameters[0]->setData( QDate( 2013, 04, 29 ) );
    parameters[1]->setData( QDate( 2013, 05, 04 ) );
  }

  QTime startTime;
  startTime.start();
  ui->wgt_ReportViewer->exec( reportDocument );
  delete reportDocument;
  reportDocument = NULL;
  ui->statusBar->showMessage( tr( "Отчет сформирова за %1мс." ).arg( startTime.elapsed() ), 5000 );
}
