#ifndef CREATEDOCSPAGE_H
#define CREATEDOCSPAGE_H

#include <QWizardPage>

#include "documentsmodel.h"


namespace Ui {
  class CreateDocsPage;
}

class CreateDocsPage : public QWizardPage
{
    Q_OBJECT


  public:
    explicit CreateDocsPage( const QStringList &doctypes, QWidget *parent = 0 );
    ~CreateDocsPage();

    int nextId() const;
    void initializePage();

    bool isComplete() const;

    DocumentsModel * createdDocs() const;
    void setDocumentCreationMode( int documentMode );


  private slots:
    void on_tBt_Create_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tBt_Delete_clicked();

  private:
    Ui::CreateDocsPage *ui;

    QStringList m__Doctypes;
    DocumentsModel *m__Documents;
    int m__DocumentMode;

    void setCreateText( const QString &text );
};

#endif // CREATEDOCSPAGE_H
