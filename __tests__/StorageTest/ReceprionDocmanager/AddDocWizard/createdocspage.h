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
    explicit CreateDocsPage( QWidget *parent = NULL );
    ~CreateDocsPage();

    int nextId() const;
    void initializePage();
    bool isComplete() const;

    DocumentsModel * createdDocs() const;
    void setDocumentCreationMode( int documentMode );
    void setDoctypes( const QStringList &doctypes );


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
