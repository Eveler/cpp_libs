#ifndef MRECIPIENTDATASOURCE_H
#define MRECIPIENTDATASOURCE_H

#include "mabstractdatasource.h"


class MRecipientDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MRecipientDataSource( QObject *parent = NULL );
    ~MRecipientDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MRECIPIENTDATASOURCE_H
