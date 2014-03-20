#ifndef MDOCTYPEDATASOURCE_H
#define MDOCTYPEDATASOURCE_H

#include "mabstractdatasource.h"


class MDoctypeDataSource : public MAbstractDataSource
{
    Q_OBJECT
  public:
    explicit MDoctypeDataSource( QObject *parent = NULL );
    ~MDoctypeDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MDOCTYPEDATASOURCE_H
