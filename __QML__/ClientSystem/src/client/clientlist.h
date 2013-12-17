#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <QObject>

#include "clientinfo.h"

#include <QtQml>


class ClientList_P;
class ClientLoader;
class Client;

class ClientList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ClientList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QList<QObject *> list READ listAsQObjects NOTIFY countChanged)
    friend class ClientLoader;


  public:
    ClientList(QObject *parent = 0);
    ~ClientList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Client * client( int index ) const;
    Q_INVOKABLE int clientIndex( Client *client ) const;
    Q_INVOKABLE Client * addLink( Client *link ) const;

    const QList<Client *> & list() const;
    QList<QObject *> listAsQObjects() const;

    Q_INVOKABLE Client * find( QVariant identifier ) const;


  signals:
    void countChanged() const;
    void clientAdded( Client *client ) const;
    void clientRemoved( int index ) const;


  private:
    ClientList_P *p;


  private slots:
    void receivedClientInfo( ClientInfo clientinfo ) const;
    void clientDestroyed();
};

QML_DECLARE_TYPE(ClientList)

#endif // CLIENTLIST_H
