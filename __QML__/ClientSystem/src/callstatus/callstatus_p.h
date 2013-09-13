#ifndef CALLSTATUS_P_H
#define CALLSTATUS_P_H

#include <QObject>

#include "callstatus.h"


class Callstatus_P : public QObject
{
    Q_OBJECT
    friend class Callstatus;


public:


signals:


public slots:


private:
    Callstatus *m__Link;
    QString m__NullString;

    explicit Callstatus_P( Callstatus *parent );

    Callstatus *p_dptr() const;
};

#endif // CALLSTATUS_P_H
