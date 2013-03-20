#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QCryptographicHash>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_toolButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(
        this, tr( "Выберете файл" ), qApp->applicationDirPath() );
  QFile f( fileName );
  if ( !f.exists() ) return;

  if ( !f.open( QFile::ReadOnly ) )
  {
    QMessageBox::warning( this, tr( "Ошибка" ), f.errorString() );
    return;
  }

  ui->lineEdit->setText( QCryptographicHash::hash( f.readAll(), QCryptographicHash::Md5 ).toHex() );
  f.close();
}
