#ifndef HUMANINFO_H
#define HUMANINFO_H

#include <QtCore>


class HumanInfo
{
  public:
    HumanInfo();
    HumanInfo( const HumanInfo &other );
    ~HumanInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname( const QString &surname );

    const QString & firstname() const;
    void setFirstname( const QString &firstname );

    const QString & lastname() const;
    void setLastname( const QString &lastname );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & email() const;
    void setEmail( const QString &email );


  private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
    QString m__Address;
    QString m__Phone;
    QString m__Email;
};

#endif // HUMANINFO_H
