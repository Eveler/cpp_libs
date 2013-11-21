#ifndef SERVICELIST_H
#define SERVICELIST_H

#include <QObject>

#include "serviceinfo.h"

#include <QtQml>


class ServiceList_P;
class ServiceLoader;
class Service;

class ServiceList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServiceList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class ServiceLoader;


public:
    ServiceList(QObject *parent = 0);
    ~ServiceList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Service * service( int index ) const;
    Q_INVOKABLE int serviceIndex( Service *service ) const;
    Q_INVOKABLE Service * addLink( Service *link ) const;


signals:
    void countChanged() const;
    void serviceAdded( Service *service ) const;
    void serviceRemoved( int index ) const;


private:
    ServiceList_P *p;


private slots:
    void receivedServiceInfo( ServiceInfo serviceInfo ) const;
    void serviceDestroyed();
};

QML_DECLARE_TYPE(ServiceList)

#endif // SERVICELIST_H
