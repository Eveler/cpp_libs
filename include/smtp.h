#ifndef SMTP_H
#define SMTP_H

#include <QCoreApplication>
//#include <QMessageBox>
#include <QtDebug>
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp( const QString &host,const QString &from, const QString &to,  const QString
&subject, const QString &body );
    ~Smtp();

signals:
    void status( const QString & );

private slots:
    void readyRead();
    void connected();

#ifdef _DEBUG_
  void stateChanged( QAbstractSocket::SocketState socketState );
#endif
  void errorReceived( QAbstractSocket::SocketError socketError );
  void disconnected();

private:
    enum State {
  Init,
  Mail,
  Rcpt,
  Data,
  Body,
  Quit,
  Close
    };

    QString message;
    QString from;
    QString rcpt;
    QTcpSocket * socket;
    QTextStream * t;
    int state;
    QString response;
};

#endif
