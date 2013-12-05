#ifndef CALLSTATUSLIST_H
#define CALLSTATUSLIST_H

#include <QObject>

#include "callstatusinfo.h"

#include <QtQml>


class CallstatusList_P;
class CallstatusLoader;
class Callstatus;

class CallstatusList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CallstatusList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class CallstatusLoader;


public:
    CallstatusList(QObject *parent = 0);
    ~CallstatusList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Callstatus * callstatus( int index ) const;
    Q_INVOKABLE int callstatusIndex( Callstatus *callstatus ) const;
    Q_INVOKABLE Callstatus * addLink( Callstatus *link ) const;

    Q_INVOKABLE Callstatus * find( QVariant identifier ) const;


signals:
    void countChanged() const;
    void callstatusAdded( Callstatus *callstatus ) const;
    void callstatusRemoved( int index ) const;


private:
    CallstatusList_P *p;


private slots:
    void addCallstatus( CallstatusInfo callstatusInfo ) const;
    void editCallstatus( CallstatusInfo callstatusInfo ) const;
    void callstatusDestroyed();
};

QML_DECLARE_TYPE(CallstatusList)

#endif // CALLSTATUSLIST_H
