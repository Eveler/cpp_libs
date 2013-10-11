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
  connect( docmanager, SIGNAL(error(QString)), SLOT(storageError(QString)) );
  connect( docmanager, SIGNAL(declarSet(QVariant)), SLOT(declarChanged()) );

  ui->wgt_ReceptionDocmanager->setDocmanager( docmanager );
  ui->wgt_ReceptionDocmanager->setDoctypes(
        QStringList() << tr( "Заявление" ) << tr( "Заявление о приостановке" ) <<
        tr( "Заявление об аннулировании" ) << tr( "Паспорт гражданина РФ" ) <<
        tr( "Расписка МФЦ" ) );

  pBar = new QProgressBar( ui->statusBar );
  pBar->setVisible( false );
  ui->statusBar->addWidget( pBar );

  ui->wgt_DeclarDocsButtons->setEnabled( false );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::storageError( QString text )
{
  QMessageBox::warning( this, tr( "Ошибка" ), text );
}

void MainWindow::declarChanged()
{
  ui->tableView->setModel( docmanager->sortedDeclarDocuments() );
  ui->wgt_DeclarDocsButtons->setEnabled( true );
}

void MainWindow::progress( qint64 cur, qint64 all )
{
  pBar->setRange( 0, all );
  pBar->setValue( cur );
}

void MainWindow::on_toolButton_clicked()
{
  docmanager->setDeclar( ui->spinBox->value() );
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
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
                           tr( "Паспорт гражданина РФ" ) << tr( "Расписка МФЦ" ),
                           QStringList() );
  if ( doc == NULL )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
  }
  else if ( docmanager->declarDocuments()->addDocument( doc ) )
  {
    QFileInfo fi( doc->localFile() );
    QString newPath = tr( "%1/temp/%2" ).arg( qApp->applicationDirPath(), fi.fileName() );
    if ( !QFile::copy( fi.absoluteFilePath(), newPath ) )
    {
      QMessageBox::warning( this, tr( "Ошибка" ),
                            tr( "Ошибка прикопировании файла:\nиз %1\nв %2" ).arg(
                              fi.absoluteFilePath(), newPath ) );
      return;
    }
    doc->setLocalFile( newPath );
    QFile::remove( fi.absoluteFilePath() );
    docmanager->save();
  }
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
