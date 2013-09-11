#ifndef USERLIST_P_H
#define USERLIST_P_H

#include <QThread>

#include "userlist.h"

#include <QHash>


class UserList_P : public QThread
{
    Q_OBJECT
    friend class UserList;


public:


signals:
    void sendError( QString errorText );
    void sendUserInfo( UserInfo );


public slots:


protected:
    void run();


private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QList<User *> m__Users;

    explicit UserList_P( UserList *parent );
    ~UserList_P();

    UserList * p_dptr() const;

};

#endif // USERLIST_P_H
