#ifndef CLIENT_P_H
#define CLIENT_P_H

#include <QObject>

#include "client.h"


class Client_P : public QObject
{
    Q_OBJECT
    friend class Client;


public:


signals:


public slots:


private:
    Client *m__Link;
    QString m__NullString;

    explicit Client_P( Client *parent );

    Client *p_dptr() const;
};

#endif // CLIENT_P_H
