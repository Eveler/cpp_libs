#ifndef DEPARTMENTLOADER_P_H
#define DEPARTMENTLOADER_P_H

#include <QThread>

#include "departmentloader.h"
#include "departmentlist.h"

#include <QHash>


class DepartmentLoader_P : public QThread
{
    Q_OBJECT
    friend class DepartmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendDepartmentInfo( DepartmentInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    DepartmentList *m__Source;

    explicit DepartmentLoader_P( DepartmentLoader *parent );
    ~DepartmentLoader_P();

    DepartmentLoader * p_dptr() const;
};

#endif // DEPARTMENTLOADER_P_H
