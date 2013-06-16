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
  explicit FTPTransfer( QObject *parent = 0);
  ~FTPTransfer();

  bool listen( QHostAddress localAddress );

  QHostAddress address() const;
  quint16 port() const;

  void setBuffer( QIODevice *buffer );
  bool startUploading();

  void setTransferMode(bool isPassive=true);
  bool isPassive() const;

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

  bool passive;
  QTcpSocket *transfer;

  bool uploadNext();

private slots:
  void incomingConnection();
  void receivedData();
  void bytesWritten( qint64 size );
  void disconnectClient();
  void connectionClosed();
};

#endif // FTPTRANSFER_H
