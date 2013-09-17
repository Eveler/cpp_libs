#ifndef HUMANLIST_H
#define HUMANLIST_H

#include <QObject>

#include "humaninfo.h"

#include <QtQml>


class HumanList_P;
class HumanLoader;
class Human;

class HumanList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HumanList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class HumanLoader;


public:
    HumanList(QObject *parent = 0);
    ~HumanList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Human * human( int index ) const;
    Q_INVOKABLE int humanIndex( Human *human ) const;
    Q_INVOKABLE Human * addLink( Human *link ) const;


signals:
    void countChanged() const;
    void humanAdded( Human *human ) const;
    void humanRemoved( int index ) const;


private:
    HumanList_P *p;


private slots:
    void receivedHumanInfo( HumanInfo humanInfo ) const;
    void humanDestroyed();
};

QML_DECLARE_TYPE(HumanList)

#endif // HUMANLIST_H
