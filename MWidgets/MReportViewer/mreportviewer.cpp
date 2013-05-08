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

  ui->webView->setHtml( reportDocument->exec() );
  ui->webView->page()->setContentEditable( true );

  return true;
}

const QString & MReportViewer::html() const
{
  return ui->webView->page()->mainFrame()->toHtml();
}
