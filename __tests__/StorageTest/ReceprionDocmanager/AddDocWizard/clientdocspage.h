#ifndef CLIENTDOCSPAGE_H
#define CLIENTDOCSPAGE_H

#include <QWizardPage>

#include "docmanager.h"


namespace Ui {
  class ClientDocsPage;
}

class ClientDocsPage : public QWizardPage
{
    Q_OBJECT


  public:
    explicit ClientDocsPage( QWidget *parent = 0 );
    ~ClientDocsPage();

    int nextId() const;
    bool isComplete() const;

    void firstStart();
    void setDocmanager( Docmanager *docmanager );
    void addClient( const QVariant &id, const QString &clientInfo );
    const QList<MFCDocumentInfo *> & selectedDocuments() const;


  private:
    Ui::ClientDocsPage *ui;

    Docmanager *m__Docmanager;
    QVariantList m__ClientIds;
    bool m__CanLoadClientDocs;
    DocumentsModel *m__Documents;
    QList<MFCDocumentInfo *> m__SelectedDocs;

    void setCanLoadClientDocs( bool can );


  private slots:
    void clientDocsViewerChanged();
    void hRangeChanged( int min, int max );
    void vRangeChanged( int min, int max );
    void progress( qint64 cur, qint64 all );

    void on_cBox_Client_currentIndexChanged(int index);
    void on_tView_ClientDocs_doubleClicked(const QModelIndex &index);
};

#endif // CLIENTDOCSPAGE_H
