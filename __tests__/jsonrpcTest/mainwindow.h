#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qjsonrpchttpclient.h"
#include <QMainWindow>
#include <QAuthenticator>

namespace Ui {
class MainWindow;
}

class HttpClient: public QJsonRpcHttpClient
{
  Q_OBJECT

public:
  HttpClient(const QString &endpoint, QObject *parent = 0)
      : QJsonRpcHttpClient(endpoint, parent)
  {
      // defaults added for my local test server
      m_username = "user";
      m_password = "pass";
  }

  void setUsername(const QString &username)
  {
      m_username = username;
  }

  void setPassword(const QString &password)
  {
      m_password = password;
  }

private slots:
  virtual void handleAuthenticationRequired(QNetworkReply *reply,
                                            QAuthenticator * authenticator)
  {
    Q_UNUSED(reply)
    authenticator->setUser(m_username);
    authenticator->setPassword(m_password);
  }

private:
    QString m_username;
    QString m_password;
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_tBt_Echo_clicked();

  void on_tBt_Add_clicked();

private:
  Ui::MainWindow *ui;

  HttpClient *client;
};

#endif // MAINWINDOW_H
