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
    ~User();


signals:


public slots:


private:
};

QML_DECLARE_TYPE(User)

#endif // USER_H
