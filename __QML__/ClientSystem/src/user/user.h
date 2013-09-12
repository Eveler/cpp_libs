#ifndef USER_H
#define USER_H

#include <QObject>

#include "userinfo.h"

#include <QtQml>


class User_P;
class UserList;

class User : public QObject, public UserInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(User)
    friend class UserList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(int post READ post WRITE setPost NOTIFY postChanged)
    Q_PROPERTY(int department READ department WRITE setDepartment NOTIFY departmentChanged)
    Q_PROPERTY(bool isactive READ isactive WRITE setIsactive NOTIFY isactiveChanged)
    Q_PROPERTY(bool dismissed READ dismissed WRITE setDismissed NOTIFY dismissedChanged)
    Q_PROPERTY(QString dblogin READ dblogin WRITE setDblogin NOTIFY dbloginChanged)
    Q_PROPERTY(int direction READ direction WRITE setDirection NOTIFY directionChanged)


public:
    User( UserList *parent = 0 );
    User( UserList *parent, const UserInfo &info );
    User( UserList *parent, User *link );
    ~User();

    Q_INVOKABLE UserList * userList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname(  const QString &surname );

    const QString & firstname() const;
    void setFirstname(  const QString &firstname );

    const QString & lastname() const;
    void setLastname(  const QString &lastname );

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


signals:
    void indexChanged();
    void identifierChanged();
    void surnameChanged();
    void firstnameChanged();
    void lastnameChanged();
    void postChanged();
    void departmentChanged();
    void isactiveChanged();
    void dismissedChanged();
    void dbloginChanged();
    void directionChanged();


public slots:


private:
    User_P *p;
};

QML_DECLARE_TYPE(User)

#endif // USER_H
