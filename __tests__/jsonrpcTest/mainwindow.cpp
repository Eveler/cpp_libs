#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  client =
      new QJsonRpcHttpClient("http://127.0.0.1:9166", this);
}

MainWindow::~MainWindow()
{
  delete client;
  delete ui;
}

void MainWindow::on_tBt_Echo_clicked()
{
  QJsonRpcMessage response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("echo", tr("Hello")));

  if(response.type() == QJsonRpcMessage::Error){
    ui->textEdit->setText(response.errorData().toString());
  }else{
    QJsonDocument doc(response.toObject());
    ui->textEdit->setText(doc.toJson());
    ui->textEdit->append("\n======================================\n");
    ui->textEdit->append(response.result().toString());
  }
}

void MainWindow::on_tBt_Add_clicked()
{
  QJsonArray params;
  params.append(1);
  params.append(tr("2"));
  QJsonRpcMessage response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("add", params));

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

  while(!params.isEmpty()) params.removeLast();
  params.append(1);
  params.append(2);
  response = client->sendMessageBlocking(
        QJsonRpcMessage::createRequest("add", params));

  if(response.type() == QJsonRpcMessage::Error){
    ui->textEdit->setText(response.errorData().toString());
    ui->textEdit->append(response.errorMessage());
    ui->textEdit->append(QJsonDocument(response.toObject()).toJson());
  }else{
    QJsonDocument doc(response.toObject());
    ui->textEdit->append(doc.toJson());
    ui->textEdit->append("\n======================================\n");
    ui->textEdit->append(response.result().toVariant().toString());
  }
}
