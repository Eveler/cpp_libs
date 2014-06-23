#ifndef MUSERDATASOURCE_H
#define MUSERDATASOURCE_H

#include "mabstractdatasource.h"


class MUserDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MUserDataSource( QObject *parent = 0 );
    ~MUserDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MUSERDATASOURCE_H
