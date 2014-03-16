#ifndef MHUMANDATASOURCE_H
#define MHUMANDATASOURCE_H

#include "mabstractdatasource.h"


class MHumanDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MHumanDataSource( QObject *parent = NULL );
    ~MHumanDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

QML_DECLARE_TYPE( MHumanDataSource )

#endif // MHUMANDATASOURCE_H
