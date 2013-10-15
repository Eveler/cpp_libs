#ifndef DECLARDOCSPAGE_H
#define DECLARDOCSPAGE_H

#include <QWizardPage>

#include "docmanager.h"


namespace Ui {
  class DeclarDocsPage;
}

class DeclarDocsPage : public QWizardPage
{
    Q_OBJECT


  public:
    explicit DeclarDocsPage(QWidget *parent = 0);
    ~DeclarDocsPage();

    int nextId() const;
    bool isComplete() const;

    void setDocmanager( Docmanager *docmanager );
    const QList<MFCDocumentInfo *> & selectedDocuments() const;


  private:
    Ui::DeclarDocsPage *ui;

    Docmanager *m__Docmanager;
    DocumentsModel *m__Documents;
    QList<MFCDocumentInfo *> m__SelectedDocs;


  private slots:
    void declarDocsViewerChanged();
    void hRangeChanged( int min, int max );
    void vRangeChanged( int min, int max );
    void progress( qint64 cur, qint64 all );
    void on_tView_DeclarDocs_doubleClicked(const QModelIndex &index);
};

#endif // DECLARDOCSPAGE_H
