#ifndef RESULTWAYLIST_H
#define RESULTWAYLIST_H

#include <QObject>

#include "resultwayinfo.h"

#include <QtQml>


class ResultwayList_P;
class ResultwayLoader;
class Resultway;

class ResultwayList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultwayList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class ResultwayLoader;


  public:
    ResultwayList(QObject *parent = 0);
    ~ResultwayList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Resultway * resultway( int index ) const;
    Q_INVOKABLE int resultwayIndex( Resultway *resultway ) const;
    Q_INVOKABLE Resultway * addLink( Resultway *link ) const;


  signals:
    void countChanged() const;
    void resultwayAdded( Resultway *resultway ) const;
    void resultwayRemoved( int index ) const;


  private:
    ResultwayList_P *p;


  private slots:
    void receivedResultwayInfo( ResultwayInfo resultwayinfo ) const;
    void resultwayDestroyed();
};

QML_DECLARE_TYPE(ResultwayList)

#endif // RESULTWAYLIST_H
