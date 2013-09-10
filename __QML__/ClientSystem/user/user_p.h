#ifndef USER_P_H
#define USER_P_H

#include <QObject>

#include "user.h"


class User_P : public QObject
{
    Q_OBJECT
    friend class User;


public:


signals:


public slots:


private:
    explicit User_P( User *parent );

    User *p_dptr() const;
};

#endif // USER_P_H
