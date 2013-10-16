#include "dialog_selectdocument.h"
#include "ui_dialog_selectdocument.h"

#include "edvprocess.h"

#include <QPushButton>
#include <QMessageBox>
#include <QDesktopWidget>


Dialog_SelectDocument::Dialog_SelectDocument(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_SelectDocument)
{
  ui->setupUi(this);

  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch );

  ui->horizontalScrollBar->setMinimum( ui->tableView->horizontalScrollBar()->minimum() );
  ui->horizontalScrollBar->setMaximum( ui->tableView->horizontalScrollBar()->maximum() );
  ui->horizontalScrollBar->setPageStep( ui->tableView->horizontalScrollBar()->pageStep() );
  ui->verticalScrollBar->setMinimum( ui->tableView->verticalScrollBar()->minimum() );
  ui->verticalScrollBar->setMaximum( ui->tableView->verticalScrollBar()->maximum() );
  ui->verticalScrollBar->setPageStep( ui->tableView->verticalScrollBar()->pageStep() );

  connect( ui->tableView->horizontalHeader(), SIGNAL(geometriesChanged()),
           SLOT(docsViewerChanged()) );
  connect( ui->tableView->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(hRangeChanged(int,int)) );
  connect( ui->tableView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
           ui->horizontalScrollBar, SLOT(setValue(int)) );
  connect( ui->horizontalScrollBar, SIGNAL(valueChanged(int)),
           ui->tableView->horizontalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tableView->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(vRangeChanged(int,int)) );
  connect( ui->tableView->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tableView->verticalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tableWidget->verticalScrollBar(), SLOT(setValue(int)) );

  ui->wgt_Progress->setVisible( false );

  resize( qApp->desktop()->availableGeometry().width()*.7,
          qApp->desktop()->availableGeometry().height()*.5 );
}

Dialog_SelectDocument::~Dialog_SelectDocument()
{
  delete ui;
}

int Dialog_SelectDocument::exec()
{
  return QDialog::Rejected;
}

const QList<MFCDocumentInfo *> & Dialog_SelectDocument::exec(
    Docmanager *docmanager, DocumentsModel *documents )
{
  if ( docmanager == NULL || documents == NULL ) return m__SelectedDocs;

  if ( documents->rowCount() == 0 )
  {
    QMessageBox::information( parentWidget(), windowTitle(),
                              tr( "Список документов пуст" ) );
    return m__SelectedDocs;
  }

  ui->buttonBox->button( QDialogButtonBox::Ok )->setDisabled( true );

  m__Docmanager = docmanager;
  m__Documents = documents;
  ui->tableView->setModel( m__Documents );

  QList<MFCDocumentInfo *> docs = m__Documents->documents();
  foreach ( MFCDocumentInfo *doc, docs)
  {
    Q_UNUSED( doc );
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( row );

    QTableWidgetItem *twi = new QTableWidgetItem();
    twi->setFlags( Qt::ItemIsUserCheckable );
    ui->tableWidget->setItem( row, 0, twi );
    twi->setCheckState( Qt::Unchecked );
  }

  for ( int rIdx = m__Documents->columnCount()-1; rIdx > 6; rIdx-- )
    ui->tableView->hideColumn( rIdx );
  ui->tableView->resizeColumnsToContents();

  ui->tableView->resizeRowsToContents();
  ui->tableWidget->resizeRowsToContents();

  QDialog::exec();

  return m__SelectedDocs;
}

void Dialog_SelectDocument::docsViewerChanged()
{
  ui->tableWidget->horizontalHeader()->setMinimumHeight(
        ui->tableView->horizontalHeader()->height() );
}

void Dialog_SelectDocument::hRangeChanged( int min, int max )
{
  ui->horizontalScrollBar->setRange( min, max );
  ui->horizontalScrollBar->setPageStep( ui->tableView->horizontalScrollBar()->pageStep() );
}

void Dialog_SelectDocument::vRangeChanged( int min, int max )
{
  ui->verticalScrollBar->setRange( min, max );
  ui->verticalScrollBar->setPageStep( ui->tableView->verticalScrollBar()->pageStep() );
}

void Dialog_SelectDocument::progress( qint64 cur, qint64 all )
{
  ui->pBar->setRange( 0, all );
  ui->pBar->setValue( cur );
}

void Dialog_SelectDocument::on_tableView_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() ) return;

  MFCDocumentInfo *doc = m__Documents->document( index );
  if ( ui->tableWidget->item( index.row(), 0 )->checkState() == Qt::Checked )
  {
    ui->tableWidget->item( index.row(), 0 )->setCheckState( Qt::Unchecked );
    m__SelectedDocs.removeOne( doc );
  }
  else
  {
    disconnect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
                this, SLOT(progress(qint64,qint64)) );
    connect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
             this, SLOT(progress(qint64,qint64)) );
    ui->pBar->setValue( 0 );
    ui->wgt_Progress->setVisible( true );
    qApp->processEvents();
    bool res = m__Docmanager->loadDocument( doc );
    ui->wgt_Progress->setVisible( false );
    if ( !res || doc->url().isEmpty() ) return;

    EDVProcess elDocProc;
    if ( elDocProc.checkDocument( doc ) )
    {
      if ( elDocProc.lastError().isEmpty() )
      {
        ui->tableWidget->item( index.row(), 0 )->setCheckState( Qt::Checked );
        m__SelectedDocs << doc;
      }
      else QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
    }
  }

  ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( m__SelectedDocs.count() > 0 );
}
