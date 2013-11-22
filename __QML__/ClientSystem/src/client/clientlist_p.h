#ifndef CLIENTLIST_P_H
#define CLIENTLIST_P_H

#include <QObject>

#include "clientlist.h"
#include "client.h"


class ClientList_P : public QObject
{
    Q_OBJECT
    friend class ClientList;


  public:


  signals:


  public slots:


  private:
    QList<Client *> m__Clients;

    explicit ClientList_P( ClientList *parent );
    ~ClientList_P();

    ClientList * p_dptr() const;
};

#endif // CLIENTLIST_P_H
