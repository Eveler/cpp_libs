#ifndef MPROCEDUREDATASOURCE_H
#define MPROCEDUREDATASOURCE_H

#include "mabstractdatasource.h"


class MProcedureDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MProcedureDataSource( QObject *parent = NULL );
    ~MProcedureDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MPROCEDUREDATASOURCE_H
