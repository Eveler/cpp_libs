#include "clientdocspage.h"
#include "ui_clientdocspage.h"

#include "wizard_adddoc.h"
#include "edvprocess.h"

#include <QMessageBox>


ClientDocsPage::ClientDocsPage( QWidget *parent ) :
  QWizardPage(parent),
  ui(new Ui::ClientDocsPage),
  m__Docmanager(NULL),
  m__CanLoadClientDocs(false)
{
  ui->setupUi(this);

  setTitle( tr( "Добавление документов из ранее принятых документов у заявителя" ) );

  m__Documents = new DocumentsModel( this );
  ui->tView_ClientDocs->setModel( m__Documents );

  ui->tWidget_SelectedClientDocs->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch );

  ui->horizontalScrollBar->setMinimum( ui->tView_ClientDocs->horizontalScrollBar()->minimum() );
  ui->horizontalScrollBar->setMaximum( ui->tView_ClientDocs->horizontalScrollBar()->maximum() );
  ui->horizontalScrollBar->setPageStep( ui->tView_ClientDocs->horizontalScrollBar()->pageStep() );
  ui->verticalScrollBar->setMinimum( ui->tView_ClientDocs->verticalScrollBar()->minimum() );
  ui->verticalScrollBar->setMaximum( ui->tView_ClientDocs->verticalScrollBar()->maximum() );
  ui->verticalScrollBar->setPageStep( ui->tView_ClientDocs->verticalScrollBar()->pageStep() );

  connect( ui->tView_ClientDocs->horizontalHeader(), SIGNAL(geometriesChanged()),
           SLOT(clientDocsViewerChanged()) );
  connect( ui->tView_ClientDocs->horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(hRangeChanged(int,int)) );
  connect( ui->tView_ClientDocs->horizontalScrollBar(), SIGNAL(valueChanged(int)),
           ui->horizontalScrollBar, SLOT(setValue(int)) );
  connect( ui->horizontalScrollBar, SIGNAL(valueChanged(int)),
           ui->tView_ClientDocs->horizontalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tView_ClientDocs->verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
           SLOT(vRangeChanged(int,int)) );
  connect( ui->tView_ClientDocs->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tView_ClientDocs->verticalScrollBar(), SLOT(setValue(int)) );
  connect( ui->tWidget_SelectedClientDocs->verticalScrollBar(), SIGNAL(valueChanged(int)),
           ui->verticalScrollBar, SLOT(setValue(int)) );
  connect( ui->verticalScrollBar, SIGNAL(valueChanged(int)),
           ui->tWidget_SelectedClientDocs->verticalScrollBar(), SLOT(setValue(int)) );

  ui->wgt_Progress->setVisible( false );

  setFinalPage( true );
}

ClientDocsPage::~ClientDocsPage()
{
  m__Docmanager = NULL;
  m__ClientIds.clear();
  m__Documents->clear();
  delete m__Documents;
  m__Documents = NULL;
  m__SelectedDocs.clear();
  delete ui;
}

int ClientDocsPage::nextId() const
{
  return -1;
}

bool ClientDocsPage::isComplete() const
{
  return m__SelectedDocs.count() > 0;
}

void ClientDocsPage::firstStart()
{
  setCanLoadClientDocs( true );
  ui->cBox_Client->setCurrentIndex( -1 );
  qApp->processEvents();
  if ( ui->cBox_Client->count() == 1 )
    ui->cBox_Client->setCurrentIndex( 0 );
}

void ClientDocsPage::setDocmanager( Docmanager *docmanager )
{
  m__Docmanager = docmanager;
}

void ClientDocsPage::addClient( const QVariant &id, const QString &clientInfo )
{
  if ( m__ClientIds.contains( id ) ) return;
  setCanLoadClientDocs( false );
  m__ClientIds << id;

  ui->cBox_Client->addItem( clientInfo, id );
  ui->cBox_Client->setCurrentIndex( -1 );
}

const QList<MFCDocumentInfo *> & ClientDocsPage::selectedDocuments() const
{
  return m__SelectedDocs;
}

void ClientDocsPage::setCanLoadClientDocs( bool can )
{
  m__CanLoadClientDocs = can;
}

void ClientDocsPage::clientDocsViewerChanged()
{
  ui->tWidget_SelectedClientDocs->horizontalHeader()->setMinimumHeight(
        ui->tView_ClientDocs->horizontalHeader()->height() );
}

void ClientDocsPage::hRangeChanged( int min, int max )
{
  ui->horizontalScrollBar->setRange( min, max );
  ui->horizontalScrollBar->setPageStep( ui->tView_ClientDocs->horizontalScrollBar()->pageStep() );
}

void ClientDocsPage::vRangeChanged( int min, int max )
{
  ui->verticalScrollBar->setRange( min, max );
  ui->verticalScrollBar->setPageStep( ui->tView_ClientDocs->verticalScrollBar()->pageStep() );
}

void ClientDocsPage::progress( qint64 cur, qint64 all )
{
  ui->pBar->setRange( 0, all );
  ui->pBar->setValue( cur );
}

void ClientDocsPage::on_cBox_Client_currentIndexChanged(int index)
{
  if ( index < 0 || !m__CanLoadClientDocs || m__Docmanager == NULL ) return;

  ui->cBox_Client->setMinimumHeight(
        ui->cBox_Client->view()->visualRect(
          ui->cBox_Client->view()->model()->index( index, 0 ) ).height()+5 );

  QVariant id = ui->cBox_Client->itemData( index );

  ui->tWidget_SelectedClientDocs->clearContents();
  for ( int rIdx = ui->tWidget_SelectedClientDocs->rowCount()-1; rIdx >= 0; rIdx-- )
  {
    MFCDocumentInfo *doc = m__Documents->document( rIdx );
    if ( !m__SelectedDocs.contains( doc ) )
    {
      ui->tWidget_SelectedClientDocs->removeRow( rIdx );
      m__Documents->removeDocument( doc );
    }
  }

  QList<MFCDocumentInfo *> docpathsDocs;
  if ( m__Docmanager->docpathsDocuments() != NULL )
    docpathsDocs = m__Docmanager->docpathsDocuments()->documents();
  QList<MFCDocumentInfo *> clientDocs = m__Docmanager->clientDocuments( id )->documents();
  foreach ( MFCDocumentInfo *doc, clientDocs)
    if ( !docpathsDocs.contains( doc ) )
    {
      int row = ui->tWidget_SelectedClientDocs->rowCount();
      m__Documents->addDocument( doc );
      ui->tWidget_SelectedClientDocs->insertRow( row );

      QTableWidgetItem *twi = new QTableWidgetItem();
      twi->setFlags( Qt::ItemIsUserCheckable );
      ui->tWidget_SelectedClientDocs->setItem( row, 0, twi );
      if ( m__SelectedDocs.contains( doc ) ) twi->setCheckState( Qt::Checked );
      else twi->setCheckState( Qt::Unchecked );
    }
  for ( int rIdx = m__Documents->columnCount()-1; rIdx > 6; rIdx-- )
    ui->tView_ClientDocs->hideColumn( rIdx );
  ui->tView_ClientDocs->resizeColumnsToContents();

  ui->tView_ClientDocs->resizeRowsToContents();
  ui->tWidget_SelectedClientDocs->resizeRowsToContents();
}

void ClientDocsPage::on_tView_ClientDocs_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() || ui->wgt_Progress->isVisible() ) return;

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

  if ( ui->tWidget_SelectedClientDocs->item( index.row(), 0 )->checkState() == Qt::Checked )
  {
    ui->tWidget_SelectedClientDocs->item( index.row(), 0 )->setCheckState( Qt::Unchecked );
    m__SelectedDocs.removeOne( doc );
  }
  else
  {
    EDVProcess elDocProc;
    if ( elDocProc.checkDocument( doc ) )
    {
      if ( elDocProc.lastError().isEmpty() )
      {
        ui->tWidget_SelectedClientDocs->item( index.row(), 0 )->setCheckState( Qt::Checked );
        m__SelectedDocs << doc;
      }
      else QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
    }
  }

  emit completeChanged();
}
