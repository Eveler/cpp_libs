#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QScopedPointer>

#include "declar-odb.hxx"
//#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  declar(QSharedPointer<declars>(new declars()))
{
  ui->setupUi(this);

//  QScopedPointer<odb::database> db(new odb::database());
  odb::database *db = new odb::pgsql::database(
        "mike", "me2db4con", "mfctest", "192.168.91.60");
  odb::transaction trans(db->begin());
  trans.tracer(odb::stderr_tracer);
  int id = 8;
  try{
    declar = db->load<declars>(id);
  }catch(const odb::exception &e){
    qWarning()<<__FILE__<<"("<<__LINE__<<")"<<e.what();
  }

  ui->textEdit->setText(tr("id=%1\nsrvid=%2\ndeclarnum=%3\ndatein=%4")
                        .arg(declar.data()->id).arg(declar.data()->srvid)
                        .arg(declar.data()->declarnum)
                        .arg(declar.data()->datein.toString("dd.MM.yyyy")));

  trans.rollback();
}

MainWindow::~MainWindow()
{
  delete ui;
//  delete declar;
}
