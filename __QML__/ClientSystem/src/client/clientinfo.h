#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QObject>

#include <QtQml>


class ClientInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ClientInfo)


  public:
    ClientInfo();
    ~ClientInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant organisationIdentifier() const;
    Q_INVOKABLE void setOrganisationIdentifier( QVariant organisationIdentifier );

    Q_INVOKABLE QVariant humanIdentifier() const;
    Q_INVOKABLE void setHumanIdentifier( QVariant humanIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__OrganisationIdentifier;
    QVariant m__HumanIdentifier;
};

QML_DECLARE_TYPE(ClientInfo)

#endif // CLIENTINFO_H
