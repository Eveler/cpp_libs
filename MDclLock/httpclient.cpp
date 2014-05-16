#include "httpclient.h"

HttpClient::HttpClient(const QString &endpoint, QObject *parent)
    : QJsonRpcHttpClient(endpoint, parent)
{
    // defaults added for my local test server
    m_username = "user";
    m_password = "pass";
}

HttpClient::HttpClient(const QString &endpoint, const QString &username,
                       const QString &password, QObject *parent)
    : QJsonRpcHttpClient(endpoint, parent)
{
    // defaults added for my local test server
    m_username = username;
    m_password = password;
}

void HttpClient::handleAuthenticationRequired(QNetworkReply *reply,
                                          QAuthenticator * authenticator)
{
  Q_UNUSED(reply)
  authenticator->setUser(m_username);
  authenticator->setPassword(m_password);
}
