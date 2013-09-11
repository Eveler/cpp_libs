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


public:
    explicit User( UserList *parent = 0 );
    explicit User( UserList *parent, const UserInfo &info );
    explicit User( UserList *parent, User *link );
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


signals:
    void indexChanged();
    void identifierChanged();
    void surnameChanged();
    void firstnameChanged();
    void lastnameChanged();


public slots:


private:
    User_P *p;

    void resetIndex();
};

QML_DECLARE_TYPE(User)

#endif // USER_H
