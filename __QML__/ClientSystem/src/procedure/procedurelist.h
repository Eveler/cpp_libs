#ifndef PROCEDURELIST_H
#define PROCEDURELIST_H

#include <QObject>

#include "procedureinfo.h"

#include <QtQml>


class ProcedureList_P;
class ProcedureLoader;
class Procedure;

class ProcedureList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcedureList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class ProcedureLoader;


public:
    ProcedureList(QObject *parent = 0);
    ~ProcedureList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Procedure * procedure( int index ) const;
    Q_INVOKABLE int procedureIndex( Procedure *procedure ) const;
    Q_INVOKABLE Procedure * addLink( Procedure *link ) const;


signals:
    void countChanged() const;
    void procedureAdded( Procedure *procedure ) const;
    void procedureRemoved( int index ) const;


private:
    ProcedureList_P *p;


private slots:
    void receivedProcedureInfo( ProcedureInfo procedureInfo ) const;
    void procedureDestroyed();
};

QML_DECLARE_TYPE(ProcedureList)

#endif // PROCEDURELIST_H
