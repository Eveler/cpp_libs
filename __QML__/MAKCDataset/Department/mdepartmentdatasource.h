#ifndef MDEPARTMENTDATASOURCE_H
#define MDEPARTMENTDATASOURCE_H

#include "mabstractdatasource.h"


class MDepartmentDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MDepartmentDataSource( QObject *parent = NULL );
    ~MDepartmentDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MDEPARTMENTDATASOURCE_H
