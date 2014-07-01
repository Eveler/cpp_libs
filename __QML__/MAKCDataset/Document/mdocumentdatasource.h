#ifndef MDOCUMENTDATASOURCE_H
#define MDOCUMENTDATASOURCE_H

#include "mabstractdatasource.h"


class MDocument;

class MDocumentDataSource : public MAbstractDataSource
{
    Q_OBJECT


  public:
    explicit MDocumentDataSource( QObject *parent = NULL );
    ~MDocumentDataSource();

    Q_INVOKABLE void findObject( QObject *documentOwner, const QString &filter = QString() );
    Q_INVOKABLE virtual void saveObject( QObject *documentOwner, MDocument *document );


  protected slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();


  private:
    QObject *m__SavedDocumentOwner;
    QObject *m__SavedDocument;
};

QML_DECLARE_TYPE( MDocumentDataSource )

#endif // MDOCUMENTDATASOURCE_H
