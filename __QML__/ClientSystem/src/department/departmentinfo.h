#ifndef DEPARTMENTINFO_H
#define DEPARTMENTINFO_H

#include <QtCore>


class DepartmentInfo
{
public:
    DepartmentInfo();
    DepartmentInfo( const DepartmentInfo &other );
    ~DepartmentInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // DEPARTMENTINFO_H
