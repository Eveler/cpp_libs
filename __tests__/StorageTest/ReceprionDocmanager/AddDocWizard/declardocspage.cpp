#include "declardocspage.h"
#include "ui_declardocspage.h"

#include "wizard_adddoc.h"
#include "edvprocess.h"

#include <QMessageBox>

#include <QDebug>


DeclarDocsPage::DeclarDocsPage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::DeclarDocsPage),
  m__Docmanager(NULL)
{
  ui->setupUi(this);

  setTitle( tr( "Выбор документов из ранее прикрепленных к делу документов" ) );

  m__Documents = new DocumentsModel( this );
  ui->tView_DeclarDocs->setModel( m__Documents );

  ui->tWidget_SelectedDeclarDocs->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch );

  ui->horizontalScrollBar->setMinimum( ui->tView_DeclarDocs->horizontalScrollBar()->minimum() );
  ui->horizontalScrollBar->setMaximum( ui->tView_DeclarDocs->horizontalScrollBar()->maximum() );
  ui->horizontalScrollBar->setPageStep( ui->tView_DeclarDocs->horizontalScrollBar()->pageStep() );
  ui->verticalScrollBar->setMinimum( ui->tView_DeclarDocs->verticalScrollBar()->minimum() );
  ui->verticalScrollBar->setMaximum( ui->tView_DeclarDocs->verticalScrollBar()->maximum() );
  ui->verticalScrollBar->setPageStep( ui->tView_DeclarDocs->verticalScrollBar()->pageStep() );

  connect( ui->tView_DeclarDocs->horizontalHeader(), SIGNAL(geometriesChanged()),
           SLOT(declarDocsViewerChanged()) );
  connect( ui->tView_DeclarDocs->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(hRangeChanged(int,int)) );
  connect( ui->tView_DeclarDocs->horizontalScrollBar(), SIGNAL(valueChanged(int)),
           ui->horizontalScrollBar, SLOT(setValue(int)) );
  connect( ui->horizontalScrollBar, SIGNAL(valueChanged(int)),
           ui->tView_DeclarDocs->horizontalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tView_DeclarDocs->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(vRangeChanged(int,int)) );
  connect( ui->tView_DeclarDocs->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tView_DeclarDocs->verticalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tWidget_SelectedDeclarDocs->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tWidget_SelectedDeclarDocs->verticalScrollBar(), SLOT(setValue(int)) );

  ui->wgt_Progress->setVisible( false );

  setFinalPage( true );
}

DeclarDocsPage::~DeclarDocsPage()
{
  m__Docmanager = NULL;
  m__Documents->clear();
  delete m__Documents;
  m__Documents = NULL;
  m__SelectedDocs.clear();
  delete ui;
}

int DeclarDocsPage::nextId() const
{
  return -1;
}

bool DeclarDocsPage::isComplete() const
{
  return m__SelectedDocs.count() > 0;
}

void DeclarDocsPage::setDocmanager( Docmanager *docmanager )
{
  m__Docmanager = docmanager;

  ui->tWidget_SelectedDeclarDocs->clearContents();
  m__Documents->clear();
  m__SelectedDocs.clear();

  QList<MFCDocumentInfo *> docpathsDocs;
  if ( m__Docmanager->docpathsDocuments() != NULL )
    docpathsDocs = m__Docmanager->docpathsDocuments()->documents();
  QList<MFCDocumentInfo *> declarDocs = m__Docmanager->declarDocuments()->documents();
  foreach ( MFCDocumentInfo *doc, declarDocs)
    if ( !docpathsDocs.contains( doc ) )
    {
      int row = ui->tWidget_SelectedDeclarDocs->rowCount();
      m__Documents->addDocument( doc );
      ui->tWidget_SelectedDeclarDocs->insertRow( row );

      QTableWidgetItem *twi = new QTableWidgetItem();
      twi->setFlags( Qt::ItemIsUserCheckable );
      ui->tWidget_SelectedDeclarDocs->setItem( row, 0, twi );
      twi->setCheckState( Qt::Unchecked );
    }

  for ( int rIdx = m__Documents->columnCount()-1; rIdx > 6; rIdx-- )
    ui->tView_DeclarDocs->hideColumn( rIdx );
  ui->tView_DeclarDocs->resizeColumnsToContents();

  ui->tView_DeclarDocs->resizeRowsToContents();
  ui->tWidget_SelectedDeclarDocs->resizeRowsToContents();
}

const QList<MFCDocumentInfo *> & DeclarDocsPage::selectedDocuments() const
{
  return m__SelectedDocs;
}

void DeclarDocsPage::declarDocsViewerChanged()
{
  ui->tWidget_SelectedDeclarDocs->horizontalHeader()->setMinimumHeight(
        ui->tView_DeclarDocs->horizontalHeader()->height() );
}

void DeclarDocsPage::hRangeChanged( int min, int max )
{
  ui->horizontalScrollBar->setRange( min, max );
  ui->horizontalScrollBar->setPageStep( ui->tView_DeclarDocs->horizontalScrollBar()->pageStep() );
}

void DeclarDocsPage::vRangeChanged( int min, int max )
{
  ui->verticalScrollBar->setRange( min, max );
  ui->verticalScrollBar->setPageStep( ui->tView_DeclarDocs->verticalScrollBar()->pageStep() );
}

void DeclarDocsPage::progress( qint64 cur, qint64 all )
{
  ui->pBar->setRange( 0, all );
  ui->pBar->setValue( cur );
}

void DeclarDocsPage::on_tView_DeclarDocs_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() ) return;

  disconnect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
              this, SLOT(progress(qint64,qint64)) );
  connect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
           this, SLOT(progress(qint64,qint64)) );
  ui->pBar->setValue( 0 );
  ui->wgt_Progress->setVisible( true );
  qApp->processEvents();
  MFCDocumentInfo *doc = m__Documents->document( index );
  bool res = m__Docmanager->loadDocument( doc );
  ui->wgt_Progress->setVisible( false );
  if ( !res || doc->url().isEmpty() ) return;

  if ( ui->tWidget_SelectedDeclarDocs->item( index.row(), 0 )->checkState() == Qt::Checked )
  {
    ui->tWidget_SelectedDeclarDocs->item( index.row(), 0 )->setCheckState( Qt::Unchecked );
    m__SelectedDocs.removeOne( doc );
  }
  else
  {
    EDVProcess elDocProc;
    if ( elDocProc.checkDocument( doc ) )
    {
      if ( elDocProc.lastError().isEmpty() )
      {
        ui->tWidget_SelectedDeclarDocs->item( index.row(), 0 )->setCheckState( Qt::Checked );
        m__SelectedDocs << doc;
      }
      else QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
    }
  }

  emit completeChanged();
}
