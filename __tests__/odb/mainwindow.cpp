#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSharedPointer>

#include "declar-odb.hxx"
#include <odb/pgsql/database.hxx>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  odb::database *db = new odb::pgsql::database(
        "mike", "me2db4con", "mfctest", "192.168.91.60");
  odb::transaction trans(db->begin());
  trans.tracer(odb::stderr_tracer);
  int id = 8;
  try{
    declar = db->load<Declar>(id).data();
  }catch(const odb::exception &e){
    qWarning()<<__FILE__<<"("<<__LINE__<<")"<<e.what();
  }

  ui->textEdit->setText(tr("id=%1\nsrvid=%2\ndeclarnum=%3\ndatein=%4")
                        .arg(declar->id).arg(declar->srvid)
                        .arg(declar->declarnum)
                        .arg(declar->datein.toString("dd.MM.yyyy")));

  trans.rollback();
}

MainWindow::~MainWindow()
{
  delete ui;
//  delete declar;
}
