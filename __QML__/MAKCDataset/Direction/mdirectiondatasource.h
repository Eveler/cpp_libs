#ifndef MDIRECTIONDATASOURCE_H
#define MDIRECTIONDATASOURCE_H

#include "mabstractdatasource.h"


class MDirectionDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MDirectionDataSource( QObject *parent = NULL );
    ~MDirectionDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MDIRECTIONDATASOURCE_H
