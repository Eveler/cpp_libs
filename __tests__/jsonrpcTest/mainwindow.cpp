#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdcllock.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  lock = MDclLock::instance();
  connect(lock, SIGNAL(error(QString)), SLOT(showError(QString)));
  MDclLock::setLogin(QUrl("http://127.0.0.1:9166"), tr("user"), tr("pass"));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_tBt_Echo_clicked()
{
  bool res = MDclLock::lock(546265, tr("declars"),
                            tr("Савенко Михаил Юрьевич"), 999);
  MDclLock::is_unlock_need(546265, tr("declars"));
  ui->tEdit_Resposes->append(tr("%1").arg(res?"true":"false"));
  if(!res)
    ui->tEdit_Resposes->append(tr("Заблокировано. Пользователь: %1")
                               .arg(MDclLock::message()));
//  res = MDclLock::lock(546265, tr("declars"),
//                            tr("Савенко Михаил Юрьевич"), 555);
//  ui->tEdit_Resposes->append(tr("%1").arg(res?"true":"false"));
//  if(!res)
//    ui->tEdit_Resposes->append(tr("Заблокировано. Пользователь: %1")
//                               .arg(MDclLock::message()));
}

void MainWindow::on_tBt_Add_clicked()
{
  MDclLock::unlock(546265, "declars");
}

void MainWindow::showError(const QString &str)
{
  ui->tEdit_Errors->append(str);
}
