#ifndef FTPTRANSFER_H
#define FTPTRANSFER_H

#include <QObject>

#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QEventLoop>
#include <QQueue>

class FTPTransfer : public QObject
{
  Q_OBJECT
public:
  enum State { State_None = 0, State_Communication };
  explicit FTPTransfer( QObject *parent = 0);
  ~FTPTransfer();

  bool listen( QHostAddress localAddress );

  QHostAddress address() const;
  quint16 port() const;

  void setBuffer( QIODevice *buffer );
  bool startUploading();

  void setTransferMode(bool isPassive=true);
  bool isPassive() const;
  bool openPassiveChanel(QString addr, quint16 port);
  void wait4communication();

  QString lastError() const;

signals:
  void dataCommunicationProgress( qint64 currentSize, qint64 overallSize );
  void dataCommunicationFinished();
  void connectionTerminated();

public slots:

private:
  QTcpServer *m__Server;
  QTcpSocket *m__Client;

  State m__State;

  QIODevice *m__Buffer;
  qint64 m__BytesDone;
  QQueue< QByteArray > dataReceived;

  bool passive;
  QTcpSocket *transfer;
  QEventLoop *loop;

  QString errStr;

  bool uploadNext();

private slots:
  void incomingConnection();
  void receivedData();
  void receivedTransferData();
  void bytesWritten( qint64 size );
  void transferBytesWritten(qint64 size);
  void disconnectClient();
  void disconnectTransfer();
  void connectionClosed();
  void transferConnectionClosed();
#ifdef FTPENGINE_DEBUG
  void transferError(QAbstractSocket::SocketError err);
  void transferSateChanged(QAbstractSocket::SocketState st);
#endif
};

#endif // FTPTRANSFER_H
