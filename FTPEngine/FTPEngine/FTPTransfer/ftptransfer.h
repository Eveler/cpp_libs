#ifndef FTPTRANSFER_H
#define FTPTRANSFER_H

#include <QObject>

#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>

class FTPTransfer : public QObject
{
  Q_OBJECT
public:
  enum State { State_None = 0, State_Communication };
  explicit FTPTransfer(QHostAddress localAddress, QObject *parent = 0);
  ~FTPTransfer();

  quint16 port() const;

signals:
  void downloadedData( QByteArray data );
  void connectionTerminated();

public slots:

private:
  QTcpServer *m__Server;
  QTcpSocket *m__Client;

  State m__State;

private slots:
  void incomingConnection();
  void receivedData();
  void connectionClosed();
};

#endif // FTPTRANSFER_H
