#ifndef declarCLIENT_P_H
#define declarCLIENT_P_H

#include <QObject>

#include "declarclient.h"


class DeclarClient_P : public QObject
{
    Q_OBJECT
    friend class DeclarClient;


public:


signals:


public slots:


private:
    DeclarClient *m__Link;
    QString m__NullString;

    explicit DeclarClient_P( DeclarClient *parent );

    DeclarClient *p_dptr() const;
};

#endif // declarCLIENT_P_H
