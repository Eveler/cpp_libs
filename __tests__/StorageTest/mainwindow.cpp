#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "amslogger.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QSqlDatabase db = QSqlDatabase::addDatabase( tr( "QPSQL" ) );
  db.setDatabaseName( tr( "MFCs" ) );
  db.setHostName( tr( "192.168.91.60" ) );
  db.setPort( 5432 );
  db.setUserName( tr( "mihail" ) );
  db.setPassword( tr( "me2db4con" ) );
  docmanager = new Docmanager( db, this );
  connect( docmanager, SIGNAL(error(QString)), SLOT(storageError(QString)) );
  connect( docmanager, SIGNAL(declarSet(QVariant)), SLOT(declarChanged()) );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::loadedDocument( MFCDocumentInfo *doc )
{
  LogDebug() << doc->localFile();
}

void MainWindow::storageError( QString text )
{
  QMessageBox::warning( this, tr( "Ошибка" ), text );
}

void MainWindow::declarChanged()
{
  ui->tableView->setModel( docmanager->sortedDeclarDocuments() );
}

void MainWindow::on_toolButton_clicked()
{
  docmanager->setDeclar( ui->spinBox->value() );
//  ftpStor->load( tr( "/docs/2013/10/05/148437_5a6dcfc8-aaa0-4fbc-b810-a6729af2cb44.mdoc" ) );
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
  MFCDocumentInfo *doc = docmanager->declarDocument( index );
  LogDebug() << doc->type();
  docmanager->loadDocument( doc );
}
