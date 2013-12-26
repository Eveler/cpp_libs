#ifndef DEPARTMENTLOADER_P_H
#define DEPARTMENTLOADER_P_H

#include <QThread>

#include "departmentloader.h"
#include "departmentinfo.h"

#include <QSqlQuery>


class DepartmentLoader_P : public QThread
{
    Q_OBJECT
    friend class DepartmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit DepartmentLoader_P( DepartmentLoader *parent );
    ~DepartmentLoader_P();

    DepartmentLoader * p_dptr() const;

    DepartmentInfo * newInfo();
};

#endif // DEPARTMENTLOADER_P_H
