#include "checkconnection.h"
#include "amslogger.h"

CheckConnection::CheckConnection(const QString &uuid, const QString &hostName,
                                 quint16 port, QObject *parent) :
  QTcpSocket(parent)
{
  connect(this, SIGNAL(connected()),SLOT(connectedToHost()));
  connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
          SLOT(translateSocketError(QAbstractSocket::SocketError)));
  uid = uuid;
  connectToHost(hostName, port);
}

void CheckConnection::connectedToHost()
{
  int w = write(uid.toLatin1());
  if(w<0) emit error(tr("Ошибка сети: %1").arg(errorString()));
  w = write("\r\n");
  if(w<0) emit error(tr("Ошибка сети: %1").arg(errorString()));
  if(!waitForBytesWritten())
    emit error(tr("Ошибка сети: %1").arg(errorString()));
  LogDebug()<<"Connected to"<<peerName()<<"on"<<peerPort()<<"uuid ="<<uid;
}

void CheckConnection::translateSocketError(QAbstractSocket::SocketError err)
{
  QString errStr;
  switch (err) {
  case ConnectionRefusedError:
    errStr = "The connection was refused by the peer (or timed out)";
    break;
  case RemoteHostClosedError:
    errStr = "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent";
  case HostNotFoundError:
    errStr = "The host address was not found";
  case SocketAccessError:
    errStr = "The socket operation failed because the application lacked the required privileges";
  case SocketResourceError:
    errStr = "The local system ran out of resources (e.g., too many sockets)";
  case SocketTimeoutError:
    errStr = "The socket operation timed out";
  case DatagramTooLargeError:
    errStr = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes)";
  case NetworkError:
    errStr = "An error occurred with the network (e.g., the network cable was accidentally plugged out)";
  case AddressInUseError:
    errStr = "The address specified is already in use and was set to be exclusive";
  case SocketAddressNotAvailableError:
    errStr = "The address specified does not belong to the host";
  case UnsupportedSocketOperationError:
    errStr = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support)";
  case ProxyAuthenticationRequiredError:
    errStr = "The socket is using a proxy, and the proxy requires authentication";
  case SslHandshakeFailedError:
    errStr = "The SSL/TLS handshake failed, so the connection was closed";
  case UnfinishedSocketOperationError:
    errStr = "The last operation attempted has not finished yet (still in progress in the background)";
  case ProxyConnectionRefusedError:
    errStr = "Could not contact the proxy server because the connection to that server was denied";
  case ProxyConnectionClosedError:
    errStr = "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
  case ProxyConnectionTimeoutError:
    errStr = "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase";
  case ProxyNotFoundError:
    errStr = "The proxy address set with setProxy() (or the application proxy) was not found";
  case ProxyProtocolError:
    errStr = "The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood";
  case OperationError:
    errStr = "An operation was attempted while the socket was in a state that did not permit it";
  case SslInternalError:
    errStr = "The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library";
  case SslInvalidUserDataError:
    errStr = "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library";
  case TemporaryError:
    errStr = "A temporary error occurred (e.g., operation would block and socket is non-blocking)";
  case UnknownSocketError:
    errStr = "An unidentified error occurred";
  default:
    LogWarning()<<"Some other error type recieved:"<<err;
    return;
    break;
  }
  emit error(tr("%1. host = %2:%3").arg(errStr).arg(peerName()).arg(peerPort()));
}
