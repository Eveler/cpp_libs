#ifndef ORGANISATIONINFO_H
#define ORGANISATIONINFO_H

#include <QtCore>


class OrganisationInfo
{
  public:
    OrganisationInfo();
    OrganisationInfo( const OrganisationInfo &other );
    ~OrganisationInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & fullname() const;
    void setFullname( const QString &fullname );

    QVariant humanIdentifier() const;
    void setHumanIdentifier( QVariant humanIdentifier );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & email() const;
    void setEmail( const QString &email );


  private:
    QVariant m__Identifier;
    QString m__Fullname;
    QVariant m__HumanIdentifier;
    QString m__Address;
    QString m__Phone;
    QString m__Email;
};

#endif // ORGANISATIONINFO_H
