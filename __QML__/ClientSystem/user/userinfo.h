#ifndef USERINFO_H
#define USERINFO_H

#include <QtCore>

class UserInfo
{
public:
    UserInfo();
    UserInfo( const UserInfo &other );

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname(  const QString &surname );

    const QString & firstname() const;
    void setFirstname(  const QString &firstname );

    const QString & lastname() const;
    void setLastname(  const QString &lastname );

private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
};

#endif // USERINFO_H
