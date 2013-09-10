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


public:
    explicit User( UserList *parent = 0 );
    explicit User( UserList *parent, const UserInfo &info );
    explicit User( UserList *parent, User *link );
    ~User();

    Q_INVOKABLE UserList * userList() const;

    int index() const;

    void setIdentifier( QVariant identifier );


signals:
    void indexChanged();
    void identifierChanged();


public slots:


private:
    User_P *p;

    void resetIndex();
};

QML_DECLARE_TYPE(User)

#endif // USER_H
