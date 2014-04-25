#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdcllock.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  client =
      new HttpClient("http://127.0.0.1:9166", this);
}

MainWindow::~MainWindow()
{
  delete client;
  delete ui;
}

void MainWindow::on_tBt_Echo_clicked()
{
  MDclLock::lock(546265, "declars", tr("Савенко Михаил Юрьевич"), "mike", 999);
}

void MainWindow::on_tBt_Add_clicked()
{
  QJsonArray params;
  params.append(546265);
  params.append(tr("declars"));
  QJsonRpcMessage response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("unlock", params));

  if(response.type() == QJsonRpcMessage::Error){
    ui->textEdit->setText(response.errorData().toString());
    ui->textEdit->append(response.errorMessage());
    ui->textEdit->append(QJsonDocument(response.toObject()).toJson());
    ui->textEdit->append("\n**************************************\n");
  }else{
    QJsonDocument doc(response.toObject());
    ui->textEdit->setText(doc.toJson());
    ui->textEdit->append("\n======================================\n");
    ui->textEdit->append(response.result().toVariant().toString());
    ui->textEdit->append(tr("isArray: %1").arg(doc.isArray()));
    ui->textEdit->append(tr("isEmpty: %1").arg(doc.isEmpty()));
  }
}
