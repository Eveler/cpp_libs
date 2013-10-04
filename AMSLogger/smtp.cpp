#include "smtp.h"

#include <QTcpSocket>
#include <QDateTime>


Smtp::Smtp( const QString &host,const QString &from, const QString &to, const QString
&subject, const QString &body )
{
    socket = new QTcpSocket( this );
    connect( socket, SIGNAL( readyRead() ), this, SLOT( readyRead() ) );
    connect( socket, SIGNAL( connected() ), this, SLOT( connected() ) );
    connect( socket, SIGNAL( error( QAbstractSocket::SocketError) ),
this, SLOT( errorReceived( QAbstractSocket::SocketError ) ) );
    connect( socket, SIGNAL( stateChanged( QAbstractSocket::SocketState)
), this, SLOT( stateChanged( QAbstractSocket::SocketState ) ) );
    connect( socket, SIGNAL( disconnected()), this,
SLOT(disconnected() ) );
    message = QString::fromLatin1( "from: " ) +from
+QString::fromLatin1( "\nto: " ) +to +QString::fromLatin1( "\nsubject: "
) +subject +
        QString::fromLatin1("\nDate: ")+
        QLocale::c().dayName(QDate::currentDate().day(),QLocale::ShortFormat)+", "+
        QDateTime::currentDateTimeUtc().toString("d")+" "+
        QLocale::c().monthName(QDate::currentDate().month(),QLocale::ShortFormat)+" "+
        QDateTime::currentDateTimeUtc().toString("yyyy hh:mm:ss -0000")+
        QString::fromLatin1( "\n\n" ) +body +"\n";
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1(
"\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;

  // change this to correct email server address
    socket->connectToHost( (host.length()>0?host:"127.0.0.1"), 25 );

  if( socket->waitForConnected( 30000 ) )
#ifdef _DEBUG_
    qDebug()<<"smtp socket connected";
#endif

    t = new QTextStream( socket );
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

#ifdef _DEBUG_
void Smtp::stateChanged( QAbstractSocket::SocketState socketState)
{
    qDebug() <<"smtp socket stateChanged " << socketState;
}
#endif

void Smtp::errorReceived( int socketError)
{
#ifdef _DEBUG_
    qDebug() << "socket error " <<(QAbstractSocket::SocketError)socketError;
#endif
    emit status(tr("Error sending message: ")+QString::number( socketError )+
                "\n    Server response:\n"+response);
}

void Smtp::disconnected()
{
#ifdef _DEBUG_
  qDebug() <<"smtp socket disconneted";
  qDebug() << "smtp socket error "  << socket->errorString();
#endif
}

void Smtp::connected()
{
#ifdef _DEBUG_
    qDebug() << "smtp socket Connected ";
#endif
}

void Smtp::readyRead()
{
  if( !socket->canReadLine() )
    return;

  QString responseLine;

    do {
    responseLine = socket->readLine();
    response += responseLine;
    } while( socket->canReadLine() && responseLine[3] != ' ' );

#ifdef _DEBUG_
      qDebug()<<"state"<<state<<"responseLine"<<responseLine;
#endif
  responseLine.truncate( 3 );

    if ( state == Init && responseLine[0] == '2' )
    {
        // banner was okay, let's go on
#ifdef _DEBUG_
      qDebug()<<"HELO there\r\n";
#endif
        *t << "HELO there\r\n";
    t->flush();
        state = Mail;
    }
    else if ( state == Mail && responseLine[0] == '2' )
    {
        // HELLO response was okay (well, it has to be)
#ifdef _DEBUG_
      qDebug()<<"MAIL FROM: <" << from << ">\r\n";
#endif
        *t << "MAIL FROM: <" << from << ">\r\n";
    t->flush();
        state = Rcpt;
    }
    else if ( state == Rcpt && responseLine[0] == '2' )
    {
#ifdef _DEBUG_
      qDebug()<<"RCPT TO: <" << rcpt << ">\r\n";
#endif
        *t << "RCPT TO: <" << rcpt << ">\r\n";
    t->flush();
        state = Data;
    }
    else if ( state == Data && responseLine[0] == '2' )
    {
#ifdef _DEBUG_
      qDebug()<<"DATA\r\n";
#endif
        *t << "DATA\r\n";
    t->flush();
        state = Body;
    }
    else if ( state == Body && responseLine[0] == '3' )
    {
#ifdef _DEBUG_
      qDebug()<<"<<<<<<<<message" << "\r\n.\r\n";
#endif
        *t << message << "\r\n.\r\n";
    t->flush();
        state = Quit;
    }
    else if ( state == Quit && responseLine[0] == '2' )
    {
#ifdef _DEBUG_
      qDebug()<<"QUIT\r\n";
#endif
        *t << "QUIT\r\n";
        // here, we just close.
        state = Close;
    t->flush();
    }
    else if ( state == Close )
    {
      emit status( tr( "Message sent" ) );
        deleteLater();
        return;
    }
    else
    {
        // something broke.
        qWarning()<<tr( "Qt Mail Example" )<<tr( "Unexpected reply from SMTP server:\n\n" ) <<response ;
        qDebug()<<tr( "Qt Mail Example" )<<tr( "Unexpected reply from SMTP server:\n\n" ) <<response ;
        state = Close;
    }
    response = "";
}
