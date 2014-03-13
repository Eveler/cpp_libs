#ifndef MHUMANDATASOURCE_H
#define MHUMANDATASOURCE_H

#include "mdatasource.h"


class MHumanDataSource : public MDataSource
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
