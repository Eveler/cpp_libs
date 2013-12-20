#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

#include <QtQml>


class UserInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UserInfo)


public:
    UserInfo();
    ~UserInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE const QString & surname() const;
    Q_INVOKABLE void setSurname( const QString &surname );

    Q_INVOKABLE const QString & firstname() const;
    Q_INVOKABLE void setFirstname( const QString &firstname );

    Q_INVOKABLE const QString & lastname() const;
    Q_INVOKABLE void setLastname( const QString &lastname );

    Q_INVOKABLE QVariant postIdentifier() const;
    Q_INVOKABLE void setPostIdentifier( QVariant postIdentifier );

    Q_INVOKABLE QVariant departmentIdentifier() const;
    Q_INVOKABLE void setDepartmentIdentifier( QVariant departmentIdentifier );

    Q_INVOKABLE bool isactive() const;
    Q_INVOKABLE void setIsactive( bool isactive );

    Q_INVOKABLE bool dismissed() const;
    Q_INVOKABLE void setDismissed( bool dismissed );

    Q_INVOKABLE const QString & dblogin() const;
    Q_INVOKABLE void setDblogin( const QString &dblogin );

    Q_INVOKABLE QVariant directionIdentifier() const;
    Q_INVOKABLE void setDirectionIdentifier( QVariant directionIdentifier );


private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
    QVariant m__PostIdentifier;
    QVariant m__DepartmentIdentifier;
    bool m__Isactive;
    bool m__Dismissed;
    QString m__Dblogin;
    QVariant m__DirectionIdentifier;
};

QML_DECLARE_TYPE(UserInfo)

#endif // USERINFO_H
