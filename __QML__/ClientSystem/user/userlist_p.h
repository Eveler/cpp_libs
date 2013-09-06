#ifndef USERLIST_P_H
#define USERLIST_P_H

#include <QThread>

class UserList_P : public QThread
{
    Q_OBJECT
public:
    explicit UserList_P(QObject *parent = 0);


signals:


public slots:


protected:
    void run();


private:
    int operationId;
    int opInThread;
};

#endif // USERLIST_P_H
