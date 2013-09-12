#ifndef DEPARTMENTLIST_H
#define DEPARTMENTLIST_H

#include <QObject>

#include "departmentinfo.h"

#include <QtQml>


class DepartmentList_P;
class DepartmentLoader;
class Department;

class DepartmentList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DepartmentList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class DepartmentLoader;


public:
    DepartmentList(QObject *parent = 0);
    ~DepartmentList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Department * department( int index ) const;
    Q_INVOKABLE int departmentIndex( Department *department ) const;
    Q_INVOKABLE Department * addLink( Department *link ) const;


signals:
    void countChanged() const;
    void departmentAdded( Department *department ) const;
    void departmentRemoved( int index ) const;


private:
    DepartmentList_P *p;


private slots:
    void receivedDepartmentInfo( DepartmentInfo departmentInfo ) const;
    void departmentDestroyed();
};

QML_DECLARE_TYPE(DepartmentList)

#endif // DEPARTMENTLIST_H
