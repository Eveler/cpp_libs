#ifndef MDOCUMENTDATASOURCE_H
#define MDOCUMENTDATASOURCE_H

#include "mabstractdatasource.h"


class MDocumentDataSource : public MAbstractDataSource
{
    Q_OBJECT
  public:
    explicit MDocumentDataSource(QObject *parent = 0);
    ~MDocumentDataSource();


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

#endif // MDOCUMENTDATASOURCE_H
