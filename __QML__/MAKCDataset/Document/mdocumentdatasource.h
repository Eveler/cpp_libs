#ifndef MDOCUMENTDATASOURCE_H
#define MDOCUMENTDATASOURCE_H

#include "mabstractdatasource.h"


class MHuman;
class MOrganization;

class MDocumentDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MDocumentDataSource( QObject *parent = NULL );
    ~MDocumentDataSource();

    Q_INVOKABLE void findObject( MHuman *human );
    Q_INVOKABLE void findObject( MOrganization *organization );


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

QML_DECLARE_TYPE( MDocumentDataSource )

#endif // MDOCUMENTDATASOURCE_H
