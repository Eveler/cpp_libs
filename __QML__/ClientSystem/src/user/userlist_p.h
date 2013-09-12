#ifndef USERLIST_P_H
#define USERLIST_P_H

#include <QObject>

#include "userlist.h"
#include "user.h"


class UserList_P : public QObject
{
    Q_OBJECT
    friend class UserList;


public:


signals:


public slots:


private:
    QList<User *> m__Users;

    explicit UserList_P( UserList *parent );
    ~UserList_P();

    UserList * p_dptr() const;
};

#endif // USERLIST_P_H
