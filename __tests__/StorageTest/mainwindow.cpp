#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../../ElectroDocViewer/EDVProcess/edvprocess.h"

#include <QMessageBox>

#include "amslogger.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QSqlDatabase db = QSqlDatabase::addDatabase( tr( "QPSQL" ) );
  db.setDatabaseName( tr( "mfctest" ) );
  db.setHostName( tr( "192.168.91.60" ) );
  db.setPort( 5432 );
  db.setUserName( tr( "mihail" ) );
  db.setPassword( tr( "me2db4con" ) );
  docmanager = new Docmanager( db, this );
  connect( docmanager, SIGNAL(error(QString)), SLOT(error(QString)) );
  connect( docmanager, SIGNAL(declarSet(QVariant)), SLOT(declarChanged()) );

  ui->wgt_ReceptionDocmanager->setDocmanager( docmanager );
  ui->wgt_ReceptionDocmanager->setDoctypes(
        QStringList() << tr( "Заявление" ) << tr( "Заявление о приостановке" ) <<
        tr( "Заявление об аннулировании" ) << tr( "Паспорт гражданина РФ" ) <<
        tr( "Расписка МФЦ" ) );

  declarInfoLoader = new DeclarInfoLoader( db.connectionName() );
  connect( declarInfoLoader, SIGNAL(databaseError(QString)), SLOT(error(QString)) );
  connect( declarInfoLoader, SIGNAL(declarInfoLoaded(QVariant,QVariant)),
           SLOT(declarInfoLoaded(QVariant,QVariant)) );

  clientInfoLoader = new ClientInfoLoader( db.connectionName() );
  connect( clientInfoLoader, SIGNAL(databaseError(QString)), SLOT(error(QString)) );
  connect( clientInfoLoader, SIGNAL(clientInfoLoaded(QString,QString,QString,QVariant)),
           SLOT(clientInfoLoaded(QString,QString,QString,QVariant)) );

  docpathsInfoLoader = new DocpathsInfoLoader( db.connectionName() );
  connect( docpathsInfoLoader, SIGNAL(databaseError(QString)), SLOT(error(QString)) );
  connect( docpathsInfoLoader, SIGNAL(docpathInfoLoaded(QVariant)),
           SLOT(docpathInfoLoaded(QVariant)) );

  pBar = new QProgressBar( ui->statusBar );
  pBar->setVisible( false );
  ui->statusBar->addWidget( pBar );

  ui->wgt_DeclarDocsButtons->setEnabled( false );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::error( QString text )
{
  QMessageBox::warning( this, tr( "Ошибка" ), text );
}

void MainWindow::declarChanged()
{
  ui->tableView->setModel( docmanager->sortedDeclarDocuments() );
  ui->wgt_DeclarDocsButtons->setEnabled( true );

  clientInfoLoader->load( ui->wgt_ReceptionDocmanager->declar() );
  docpathsInfoLoader->load( ui->wgt_ReceptionDocmanager->declar() );
  ui->tView_DocpathDocs->setModel( docmanager->docpathsDocuments() );

}

void MainWindow::progress( qint64 cur, qint64 all )
{
  pBar->setRange( 0, all );
  pBar->setValue( cur );
}

void MainWindow::declarInfoLoaded( QVariant id, QVariant serviceId )
{
  RequiredDocs *req = new RequiredDocs( serviceId, QSqlDatabase::database(), QString(), this );
  ui->wgt_ReceptionDocmanager->setRequiredDocs( req );

  ui->wgt_ReceptionDocmanager->setDeclar( id );
}

void MainWindow::clientInfoLoaded( QString fio, QString phone, QString address, QVariant id )
{
  ui->listWidget->addItem(
        tr( "%1\n%2\n%3" ).arg( fio, phone, address ) );
  ui->wgt_ReceptionDocmanager->addClient(
        id, tr( "%1\n%2\n%3" ).arg( fio, phone, address ) );
}

void MainWindow::docpathInfoLoaded( QVariant id )
{
  ui->lWgt_Steps->setFocus();
  ui->lWgt_Steps->addItem( id.toString() );
  ui->lWgt_Steps->setCurrentRow( -1 );
  ui->wgt_ReceptionDocmanager->addDocpaths( id );
}

void MainWindow::on_toolButton_clicked()
{
  ui->listWidget->clear();
  ui->lWgt_Steps->clear();

  declarInfoLoader->load( ui->spinBox->value() );
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() ) return;

  disconnect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
              this, SLOT(progress(qint64,qint64)) );
  connect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
           this, SLOT(progress(qint64,qint64)) );
  pBar->setValue( 0 );
  pBar->setVisible( true );
  qApp->processEvents();
  MFCDocumentInfo *doc = docmanager->declarDocument( index );
  bool res = docmanager->loadDocument( doc );
  pBar->setVisible( false );

  if ( !res || doc->url().isEmpty() ) return;
  EDVProcess elDocProc;
  if ( !elDocProc.readDocument( doc ) )
    QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
}

void MainWindow::on_tBt_AddDeclarDoc_clicked()
{
  EDVProcess elDocProc;
  MFCDocumentInfo *doc = elDocProc.writeDocument(
                           QStringList() << tr( "Заявление" ) <<
                           tr( "Паспорт гражданина РФ" ) << tr( "Расписка МФЦ" ) );
  if ( doc == NULL )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else if ( docmanager->declarDocuments()->addDocument( doc ) )
    docmanager->save();
}

void MainWindow::on_tBt_CheckDeclarDoc_clicked()
{
  QModelIndex index = ui->tableView->currentIndex();
  if ( !index.isValid() ) return;

  disconnect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
              this, SLOT(progress(qint64,qint64)) );
  connect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
           this, SLOT(progress(qint64,qint64)) );
  pBar->setValue( 0 );
  pBar->setVisible( true );
  qApp->processEvents();
  MFCDocumentInfo *doc = docmanager->declarDocument( index );
  bool res = docmanager->loadDocument( doc );
  pBar->setVisible( false );

  if ( !res || doc->url().isEmpty() ) return;
  EDVProcess elDocProc;
  if ( !elDocProc.checkDocument( doc ) )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else QMessageBox::information( this, tr( "Проверка" ), tr( "Документ подтвержден!" ) );
}

void MainWindow::on_lWgt_Steps_currentRowChanged( int currentRow )
{
  QListWidgetItem *lwi = ui->lWgt_Steps->item( currentRow );
  if ( lwi == NULL || docmanager->currentDocpath().toString() == lwi->text() )
    return;

  ui->wgt_ReceptionDocmanager->setCurrentDocpaths( lwi->text().toInt() );
  ui->tView_DocpathDocs->setModel( docmanager->docpathsDocuments() );
}

void MainWindow::on_tView_DocpathDocs_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() ) return;

  disconnect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
              this, SLOT(progress(qint64,qint64)) );
  connect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
           this, SLOT(progress(qint64,qint64)) );
  pBar->setValue( 0 );
  pBar->setVisible( true );
  qApp->processEvents();
  MFCDocumentInfo *doc = docmanager->docpathsDocument( index );
  bool res = docmanager->loadDocument( doc );
  pBar->setVisible( false );

  if ( !res || doc->url().isEmpty() ) return;
  EDVProcess elDocProc;
  if ( !elDocProc.readDocument( doc ) )
    QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
}

void MainWindow::on_tBt_CheckDocpathDoc_clicked()
{
  QModelIndex index = ui->tableView->currentIndex();
  if ( !index.isValid() ) return;

  disconnect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
              this, SLOT(progress(qint64,qint64)) );
  connect( docmanager, SIGNAL(dataTransferProgress(qint64,qint64)),
           this, SLOT(progress(qint64,qint64)) );
  pBar->setValue( 0 );
  pBar->setVisible( true );
  qApp->processEvents();
  MFCDocumentInfo *doc = docmanager->docpathsDocument( index );
  bool res = docmanager->loadDocument( doc );
  pBar->setVisible( false );

  if ( !res || doc->url().isEmpty() ) return;
  EDVProcess elDocProc;
  if ( !elDocProc.checkDocument( doc ) )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else QMessageBox::information( this, tr( "Проверка" ), tr( "Документ подтвержден!" ) );
}

void MainWindow::on_tBt_AddDocpathDoc_clicked()
{
  EDVProcess elDocProc;
  MFCDocumentInfo *doc = elDocProc.writeDocument(
                           QStringList() << tr( "Заявление" ) <<
                           tr( "Паспорт гражданина РФ" ) << tr( "Расписка МФЦ" ) );
  if ( doc == NULL )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else if ( docmanager->docpathsDocuments()->addDocument( doc ) )
    docmanager->save();
}
