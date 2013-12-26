#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QScopedPointer>

#include "declar-odb.hxx"
//#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  declar(new Declar())
{
  ui->setupUi(this);

//  QScopedPointer<odb::database> db(new odb::database());
  odb::database *db = new odb::pgsql::database(
        "mike", "me2db4con", "mfctest", "192.168.91.60");
  odb::transaction trans(db->begin());
  trans.tracer(odb::stderr_tracer);

  trans.rollback();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete declar;
}
