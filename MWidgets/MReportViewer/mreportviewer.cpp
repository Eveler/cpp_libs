#include "mreportviewer.h"
#include "ui_mreportviewer.h"

#include "mreportviewer_p.h"

#include <QMessageBox>
#include <QWebFrame>

#include <QDebug>


MReportViewer::MReportViewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MReportViewer)
{
  ui->setupUi(this);

  p = new MReportViewer_P( this );
  ui->progressBar->setVisible( false );
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

  if ( !exec( reportDocument ) )
  {
    delete reportDocument;
    reportDocument = NULL;
  }
}

bool MReportViewer::exec( MReportDocument *reportDocument )
{
  ui->webView->setHtml( QString() );
  if ( reportDocument == NULL ) return true;

  if ( !p->populate( reportDocument ) ) return false;

  ui->progressBar->setValue( 0 );
  ui->progressBar->setVisible( true );
  connect( reportDocument, SIGNAL(progress(int,int)), SLOT(reportProgress(int,int)) );

  ui->webView->setHtml( reportDocument->exec() );
  ui->webView->page()->setContentEditable( true );
  ui->progressBar->setVisible( false );

  return true;
}

QString MReportViewer::html() const
{
  return ui->webView->page()->mainFrame()->toHtml();
}

void MReportViewer::reportProgress( int current, int overall )
{
  emit progress( current, overall );
  ui->progressBar->setValue( current );
  ui->progressBar->setFormat( QString::number( (double)current/100. )+"%" );
  qApp->processEvents();
}
