#include "dialog_selectdocument.h"
#include "ui_dialog_selectdocument.h"

#include "edvprocess.h"
#include "dialog_docdetails.h"

#include <QPushButton>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QMenu>


Dialog_SelectDocument::Dialog_SelectDocument(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_SelectDocument),
  m__Docmanager(NULL),
  m__Documents(NULL),
  m__AutoExclusive(false),
  m__OnlyAllSelect(false),
  m__OriginalsCopies(true)
{
  ui->setupUi(this);

  setCreatableDoctypes( QStringList() );

#if QT_VERSION<0x050000
  ui->tableWidget->horizontalHeader()->setResizeMode(
        QHeaderView::Stretch );
#else
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch );
#endif

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

void Dialog_SelectDocument::setAutoExclusive( bool autoExclusive )
{
  m__AutoExclusive = autoExclusive;
  if ( m__AutoExclusive ) setOnlyAllSelect( false );
}

bool Dialog_SelectDocument::autoExclusive() const
{
  return m__AutoExclusive;
}

void Dialog_SelectDocument::setOnlyAllSelect( bool onlyAllSelect )
{
  m__OnlyAllSelect = onlyAllSelect;
  if ( m__OnlyAllSelect ) setAutoExclusive( false );
}

void Dialog_SelectDocument::setOriginalsCopies( bool originalsCopies )
{
  m__OriginalsCopies = originalsCopies;
}

bool Dialog_SelectDocument::originalsCopies() const
{
  return m__OriginalsCopies;
}

void Dialog_SelectDocument::setCreatableDoctypes( const QStringList &doctypes )
{
  if ( ui->tBt_Create->menu() == NULL )
    ui->tBt_Create->setMenu( new QMenu );

  while ( !ui->tBt_Create->menu()->actions().isEmpty() )
  {
    QAction *action = ui->tBt_Create->menu()->actions().first();
    ui->tBt_Create->menu()->removeAction( action );
    delete action;
    action = NULL;
  }

  foreach ( QString doctype, doctypes )
    ui->tBt_Create->menu()->addAction( doctype );

  ui->wgt_ToolButtons->setVisible( !doctypes.isEmpty() );
}


void Dialog_SelectDocument::setDocagencies( const QStringList &docagencies )
{
  m__Docagencies = docagencies;
}

const QList<MFCDocumentInfo *> & Dialog_SelectDocument::exec(
    const Docmanager *docmanager, DocumentsModel *documents, const QString &clientInfo )
{
  if ( docmanager == NULL || documents == NULL ) return m__SelectedDocs;


  ui->buttonBox->button( QDialogButtonBox::Ok )->setDisabled( true );

  disconnect( m__Docmanager, SIGNAL(error(QString)), this, SLOT(docmanagerError(QString)) );
  m__Docmanager = docmanager;
  connect( m__Docmanager, SIGNAL(error(QString)), this, SLOT(docmanagerError(QString)) );
  m__Documents = documents;
  ui->tableView->setModel( m__Documents );
  ui->l_Client->setText( clientInfo );
  ui->groupBox->setVisible( !clientInfo.isEmpty() );

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

  for ( int rIdx = m__Documents->columnCount()-4; rIdx > 6; rIdx-- )
    ui->tableView->hideColumn( rIdx );
  ui->tableView->hideColumn( m__Documents->columnCount()-1 );
  ui->tableView->resizeColumnsToContents();

  ui->tableView->resizeRowsToContents();
  ui->tableWidget->resizeRowsToContents();

  if ( m__Documents->rowCount() == 1 )
  {
    QTimer *timer = new QTimer( this );
    timer->singleShot( 100, this, SLOT(activateSingleDocument()) );
    timer = NULL;
  }
  if ( QDialog::exec() == QDialog::Rejected )
    m__SelectedDocs.clear();

  while ( !m__CreatedDocs.isEmpty() )
  {
    MFCDocumentInfo *doc = m__CreatedDocs.takeFirst();
    if ( !m__SelectedDocs.contains( doc ) )
      MFCDocumentInfo::remove( doc );
    doc = NULL;
  }

  return m__SelectedDocs;
}

int Dialog_SelectDocument::exec()
{
  return QDialog::Rejected;
}

bool Dialog_SelectDocument::isCompleted() const
{
  return ( m__OnlyAllSelect ?
             m__SelectedDocs.count() > 0 &&
             m__SelectedDocs.count() == m__Documents->rowCount() :
             m__SelectedDocs.count() > 0 );
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

void Dialog_SelectDocument::activateSingleDocument()
{
  on_tableView_doubleClicked( ui->tableView->model()->index( 0, 0 ) );
}

void Dialog_SelectDocument::docmanagerError( QString error )
{
  QMessageBox::warning( this, tr( "Ошибка" ), error );
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
    if ( ui->wgt_Progress->isVisible() ) return;
    if ( !doc->revoker().isEmpty() )
    {
      foreach ( QAction *action_Doctype, ui->tBt_Create->menu()->actions() )
        if ( action_Doctype->text() == doc->type() )
        {
          QMessageBox::information( this, tr( "Документ аннулирован" ), tr( "Документ «%1» аннулирован пользователем %2 %3" )
                                    .arg( doc->type() ).arg( doc->revoker() ).arg( doc->revoked().toString( "dd.MM.yyyy 'года в' h 'ч.' m 'мин.'" ) ) );
          action_Doctype->trigger();
          break;
        }
      return;
    }

    disconnect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
                this, SLOT(progress(qint64,qint64)) );
    connect( m__Docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
             this, SLOT(progress(qint64,qint64)) );
    ui->pBar->setValue( 0 );
    ui->wgt_Progress->setVisible( true );
    qApp->processEvents();
    bool res = ( m__Docmanager->allDocuments()->documents().contains( doc ) &&
                 !doc->url().isEmpty()?
                   m__Docmanager->loadDocument( doc ) : true );
    ui->wgt_Progress->setVisible( false );
    if ( !res ) return;

    if ( doc->url().isEmpty() && doc->localFile().isEmpty() )
    {
      Dialog_DocDetails dDocDetails( this );
      dDocDetails.setWindowTitle( tr( "Введите количество экземпляров и листов" ) );
      if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
        return;

      if ( m__AutoExclusive && !m__SelectedDocs.isEmpty() )
      {
        int desIdx = m__Documents->documentRow( m__SelectedDocs.takeFirst() );
        ui->tableWidget->item( desIdx, 0 )->setCheckState( Qt::Unchecked );
      }

      ui->tableWidget->item( index.row(), 0 )->setCheckState( Qt::Checked );
      m__SelectedDocs << doc;
    }
    else
    {
      if ( doc->localFile().isEmpty() ) return;

      EDVProcess elDocProc;
      if ( elDocProc.checkDocument( doc ) )
      {
        if ( elDocProc.lastError().isEmpty() )
        {
          if ( m__OriginalsCopies )
          {
            Dialog_DocDetails dDocDetails( this );
            dDocDetails.setWindowTitle( tr( "Введите количество экземпляров и листов" ) );
            if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
              return;
          }
          else
          {
            doc->setOriginalExemplars( 0 );
            doc->setOriginalPages( 0 );
            doc->setCopyExemplars( 0 );
            doc->setCopyPages( 0 );
          }

          if ( m__AutoExclusive && !m__SelectedDocs.isEmpty() )
          {
            int desIdx = m__Documents->documentRow( m__SelectedDocs.takeFirst() );
            ui->tableWidget->item( desIdx, 0 )->setCheckState( Qt::Unchecked );
          }

          ui->tableWidget->item( index.row(), 0 )->setCheckState( Qt::Checked );
          m__SelectedDocs << doc;
        }
        else QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
      }
    }
  }

  ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( isCompleted() );
}

void Dialog_SelectDocument::on_tBt_Create_triggered(QAction *arg1)
{
  EDVProcess elDocProc;
  MFCDocumentInfo *doc = elDocProc.writeDocument(
                           QStringList() << arg1->text(), QString(), QString(), QString(),
                           QDate(), QDate(), m__Docagencies );
  if ( doc == NULL )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else
  {
    if ( m__OriginalsCopies )
    {
      Dialog_DocDetails dDocDetails( this );
      dDocDetails.setWindowTitle( tr( "Введите количество экземпляров и листов" ) );
      if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
      {
        MFCDocumentInfo::remove( doc );
        doc = NULL;
        return;
      }
    }
    else
    {
      doc->setOriginalExemplars( 0 );
      doc->setOriginalPages( 0 );
      doc->setCopyExemplars( 0 );
      doc->setCopyPages( 0 );
    }

    if ( m__AutoExclusive && !m__SelectedDocs.isEmpty() )
    {
      int row = m__Documents->documentRow( m__SelectedDocs.takeFirst() );
      ui->tableWidget->item( row, 0 )->setCheckState( Qt::Unchecked );
    }

    m__Documents->addDocument( doc );
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( row );

    QTableWidgetItem *twi = new QTableWidgetItem();
    twi->setFlags( Qt::ItemIsUserCheckable );
    ui->tableWidget->setItem( row, 0, twi );
    twi->setCheckState( Qt::Checked );

    m__CreatedDocs << doc;
    m__SelectedDocs << doc;

    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( isCompleted() );
  }
}
