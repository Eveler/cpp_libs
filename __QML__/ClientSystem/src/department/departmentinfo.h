#ifndef DEPARTMENTINFO_H
#define DEPARTMENTINFO_H

#include <QObject>

#include <QtQml>


class DepartmentInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DepartmentInfo)


  public:
    DepartmentInfo();
    ~DepartmentInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(DepartmentInfo)

#endif // DEPARTMENTINFO_H
