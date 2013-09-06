#ifndef USERLIST_H
#define USERLIST_H

#include "user.h"


class UserList_P;

class UserList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(UserList)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    UserList(QObject *parent = 0);
    ~UserList();

    Q_INVOKABLE QString error( int operationId ) const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName ) const;

    Q_INVOKABLE bool load() const;

    int count() const;


signals:
    void lastError( int operationId );
    void connectionNameChanged();
    void countChanged();
};

QML_DECLARE_TYPE(UserList)

#endif // USERLIST_H

