#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QtCore>


class ClientInfo
{
  public:
    ClientInfo();
    ClientInfo( const ClientInfo &other );
    ~ClientInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant organisationIdentifier() const;
    void setOrganisationIdentifier( QVariant organisationIdentifier );

    QVariant humanIdentifier() const;
    void setHumanIdentifier( QVariant humanIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__OrganisationIdentifier;
    QVariant m__HumanIdentifier;
};

#endif // CLIENTINFO_H
