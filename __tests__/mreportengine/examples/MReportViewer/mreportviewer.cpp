#include "mreportviewer.h"
#include "ui_mreportviewer.h"

#include "mreportviewer_p.h"

#include <QMessageBox>

#include <QDebug>


MReportViewer::MReportViewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MReportViewer)
{
  ui->setupUi(this);

  p = new MReportViewer_P( this );
}

MReportViewer::~MReportViewer()
{
  delete ui;
}

void MReportViewer::exec( const QString &filePath )
{
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

  exec( reportDocument );
}

void MReportViewer::exec( MReportDocument *reportDocument )
{
  ui->webView->setHtml( QString() );
  if ( reportDocument == NULL ) return;

  ui->webView->setHtml( reportDocument->exec() );
  ui->webView->page()->setContentEditable( true );
}
