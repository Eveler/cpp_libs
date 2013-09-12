#ifndef USERINFO_H
#define USERINFO_H

#include <QtCore>


class UserInfo
{
public:
    UserInfo();
    UserInfo( const UserInfo &other );
    ~UserInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname( const QString &surname );

    const QString & firstname() const;
    void setFirstname( const QString &firstname );

    const QString & lastname() const;
    void setLastname( const QString &lastname );

    int post() const;
    void setPost( int post );

    int department() const;
    void setDepartment( int department );

    bool isactive() const;
    void setIsactive( bool isactive );

    bool dismissed() const;
    void setDismissed( bool dismissed );

    const QString & dblogin() const;
    void setDblogin( const QString &dblogin );

    int direction() const;
    void setDirection( int direction );


private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
    int m__Post;
    int m__Department;
    bool m__Isactive;
    bool m__Dismissed;
    QString m__Dblogin;
    int m__Direction;
};

#endif // USERINFO_H
