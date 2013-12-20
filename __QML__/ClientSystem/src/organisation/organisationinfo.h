#ifndef ORGANISATIONINFO_H
#define ORGANISATIONINFO_H

#include <QObject>

#include <QtQml>


class OrganisationInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OrganisationInfo)


  public:
    OrganisationInfo();
    ~OrganisationInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE const QString & fullname() const;
    Q_INVOKABLE void setFullname( const QString &fullname );

    Q_INVOKABLE QVariant humanIdentifier() const;
    Q_INVOKABLE void setHumanIdentifier( QVariant humanIdentifier );

    Q_INVOKABLE const QString & address() const;
    Q_INVOKABLE void setAddress( const QString &address );

    Q_INVOKABLE const QString & phone() const;
    Q_INVOKABLE void setPhone( const QString &phone );

    Q_INVOKABLE const QString & email() const;
    Q_INVOKABLE void setEmail( const QString &email );


  private:
    QVariant m__Identifier;
    QString m__Fullname;
    QVariant m__HumanIdentifier;
    QString m__Address;
    QString m__Phone;
    QString m__Email;
};

QML_DECLARE_TYPE(OrganisationInfo)

#endif // ORGANISATIONINFO_H
