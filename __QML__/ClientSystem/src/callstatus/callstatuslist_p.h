#ifndef CALLSTATUSLIST_P_H
#define CALLSTATUSLIST_P_H

#include <QObject>

#include "callstatuslist.h"
#include "callstatus.h"


class CallstatusList_P : public QObject
{
    Q_OBJECT
    friend class CallstatusList;


public:


signals:


public slots:


private:
    QList<Callstatus *> m__Callstatuss;

    explicit CallstatusList_P( CallstatusList *parent );
    ~CallstatusList_P();

    CallstatusList * p_dptr() const;
};

#endif // CALLSTATUSLIST_P_H
