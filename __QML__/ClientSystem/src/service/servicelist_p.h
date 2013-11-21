#ifndef SERVICELIST_P_H
#define SERVICELIST_P_H

#include <QObject>

#include "servicelist.h"
#include "service.h"


class ServiceList_P : public QObject
{
    Q_OBJECT
    friend class ServiceList;


public:


signals:


public slots:


private:
    QList<Service *> m__Services;

    explicit ServiceList_P( ServiceList *parent );
    ~ServiceList_P();

    ServiceList * p_dptr() const;
};

#endif // SERVICELIST_P_H
