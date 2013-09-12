#ifndef DEPARTMENT_P_H
#define DEPARTMENT_P_H

#include <QObject>

#include "department.h"


class Department_P : public QObject
{
    Q_OBJECT
    friend class Department;


public:


signals:


public slots:


private:
    Department *m__Link;
    QString m__NullString;

    explicit Department_P( Department *parent );

    Department *p_dptr() const;
};

#endif // DEPARTMENT_P_H
