#ifndef DEPARTMENTLOADER_P_H
#define DEPARTMENTLOADER_P_H

#include <QThread>

#include "departmentloader.h"
#include "departmentinfo.h"

#include <QHash>


class DepartmentLoader_P : public QThread
{
    Q_OBJECT
    friend class DepartmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( DepartmentInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit DepartmentLoader_P( DepartmentLoader *parent );
    ~DepartmentLoader_P();

    DepartmentLoader * p_dptr() const;
};

#endif // DEPARTMENTLOADER_P_H
