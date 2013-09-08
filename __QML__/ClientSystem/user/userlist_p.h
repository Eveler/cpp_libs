#ifndef USERLIST_P_H
#define USERLIST_P_H

#include <QThread>

#include <QHash>


class UserList;
class User;

class UserList_P : public QThread
{
    Q_OBJECT
    friend class UserList;


public:


signals:
    void sendError( QString errorText );
    void sendUser( User *user );


public slots:


protected:
    void run();


private:
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QList<User *> m__Users;

    explicit UserList_P( UserList *parent );
    ~UserList_P();

    UserList * p_dptr() const;

};

#endif // USERLIST_P_H
