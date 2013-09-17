#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QObject>

#include "departmentinfo.h"

#include <QtQml>


class Department_P;
class DepartmentList;

class Department : public QObject, public DepartmentInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Department)
    friend class DepartmentList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


public:
    Department( DepartmentList *parent = 0 );
    Department( DepartmentList *parent, const DepartmentInfo &info );
    Department( DepartmentList *parent, Department *link );
    ~Department();

    Q_INVOKABLE DepartmentList * departmentList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName(  const QString &name );


signals:
    void indexChanged();
    void identifierChanged();
    void nameChanged();


public slots:


private:
    Department_P *p;
};

QML_DECLARE_TYPE(Department)

#endif // DEPARTMENT_H
