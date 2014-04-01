#ifndef MORGANIZATIONDATASOURCE_H
#define MORGANIZATIONDATASOURCE_H

#include "mabstractdatasource.h"


class MOrganizationDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MOrganizationDataSource( QObject *parent = NULL );
    ~MOrganizationDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MORGANIZATIONDATASOURCE_H
