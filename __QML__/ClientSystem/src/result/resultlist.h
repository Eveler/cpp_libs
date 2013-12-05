#ifndef RESULTLIST_H
#define RESULTLIST_H

#include <QObject>

#include "resultinfo.h"

#include <QtQml>


class ResultList_P;
class ResultLoader;
class Result;

class ResultList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class ResultLoader;


  public:
    ResultList(QObject *parent = 0);
    ~ResultList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Result * result( int index ) const;
    Q_INVOKABLE int resultIndex( Result *result ) const;
    Q_INVOKABLE Result * addLink( Result *link ) const;

    Q_INVOKABLE Result * find( QVariant identifier ) const;


  signals:
    void countChanged() const;
    void resultAdded( Result *result ) const;
    void resultRemoved( int index ) const;


  private:
    ResultList_P *p;


  private slots:
    void receivedResultInfo( ResultInfo resultinfo ) const;
    void resultDestroyed();
};

QML_DECLARE_TYPE(ResultList)

#endif // RESULTLIST_H
