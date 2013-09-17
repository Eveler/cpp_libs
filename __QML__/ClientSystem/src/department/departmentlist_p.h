#ifndef DEPARTMENTLIST_P_H
#define DEPARTMENTLIST_P_H

#include <QObject>

#include "departmentlist.h"
#include "department.h"


class DepartmentList_P : public QObject
{
    Q_OBJECT
    friend class DepartmentList;


public:


signals:


public slots:


private:
    QList<Department *> m__Departments;

    explicit DepartmentList_P( DepartmentList *parent );
    ~DepartmentList_P();

    DepartmentList * p_dptr() const;
};

#endif // DEPARTMENTLIST_P_H
