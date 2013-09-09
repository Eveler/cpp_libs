#ifndef USER_H
#define USER_H

#include <QObject>

#include <QtQml>


class UserList;

class User : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(User)
    friend class UserList;

public:
    explicit User( UserList *parent = 0 );
    explicit User( UserList *parent, const User &other );
    explicit User( UserList *parent, User *link );
    ~User();

    Q_INVOKABLE UserList * userList() const;


signals:


public slots:


private:
    void resetIndex();
};

QML_DECLARE_TYPE(User)

#endif // USER_H
