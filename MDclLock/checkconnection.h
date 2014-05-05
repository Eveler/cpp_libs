#ifndef CHECKCONNECTION_H
#define CHECKCONNECTION_H

#include <QTcpSocket>

class CheckConnection : public QTcpSocket
{
  Q_OBJECT
public:
  explicit CheckConnection(const QString &uuid, const QString & hostName,
                           quint16 port, QObject *parent = 0);

signals:
  void error(QString str);

private slots:
  void connectedToHost();
  void translateSocketError(QAbstractSocket::SocketError err);

private:
  QString uid;
};

#endif // CHECKCONNECTION_H
