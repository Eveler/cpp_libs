#ifndef USERLIST_H
#define USERLIST_H

#include <QObject>

#include "userinfo.h"

#include <QtQml>


class UserList_P;
class UserLoader;
class User;

class UserList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UserList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class UserLoader;


public:
    UserList(QObject *parent = 0);
    ~UserList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE User * user( int index ) const;
    Q_INVOKABLE int userIndex( User *user ) const;
    Q_INVOKABLE User * addLink( User *link ) const;

    Q_INVOKABLE User * find( QVariant identifier ) const;


signals:
    void countChanged() const;
    void userAdded( User *user ) const;
    void userRemoved( int index ) const;


private:
    UserList_P *p;


private slots:
    void receivedUserInfo( UserInfo userInfo ) const;
    void userDestroyed();
};

QML_DECLARE_TYPE(UserList)

#endif // USERLIST_H

