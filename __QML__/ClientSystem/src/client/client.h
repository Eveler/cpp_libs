#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "clientinfo.h"

#include <QtQml>


class Client_P;
class ClientList;

class Client : public QObject, public ClientInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
    friend class ClientList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant organisationIdentifier READ organisationIdentifier
               WRITE setOrganisationIdentifier NOTIFY organisationIdentifierChanged)
    Q_PROPERTY(QVariant humanIdentifier READ humanIdentifier
               WRITE setHumanIdentifier NOTIFY humanIdentifierChanged)


  public:
    Client( ClientList *parent = 0 );
    Client( ClientList *parent, const ClientInfo &info );
    Client( ClientList *parent, Client *link );
    ~Client();

    Q_INVOKABLE ClientList * clientList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant organisationIdentifier() const;
    void setOrganisationIdentifier( QVariant organisationIdentifier );

    QVariant humanIdentifier() const;
    void setHumanIdentifier( QVariant humanIdentifier );


  signals:
    void indexChanged();
    void identifierChanged();
    void organisationIdentifierChanged();
    void humanIdentifierChanged();


  public slots:


  private:
    Client_P *p;
};

QML_DECLARE_TYPE(Client)

#endif // CLIENT_H
