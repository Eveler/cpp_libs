#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "qjsonrpchttpclient.h"
#include <QAuthenticator>

class HttpClient: public QJsonRpcHttpClient
{
  Q_OBJECT

public:
  HttpClient(const QString &endpoint, QObject *parent = 0);

  void setUsername(const QString &username){m_username = username;}

  void setPassword(const QString &password){m_password = password;}

private slots:
  virtual void handleAuthenticationRequired(QNetworkReply *reply,
                                            QAuthenticator * authenticator);

private:
    QString m_username;
    QString m_password;
};

#endif // HTTPCLIENT_H
