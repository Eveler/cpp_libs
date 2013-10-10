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


  private slots:
    void on_tBt_Create_clicked();

  private:
    Ui::CreateDocsPage *ui;

    QStringList m__Doctypes;
    DocumentsModel *m__Documents;

    void setCreateText( const QString &text );
};

#endif // CREATEDOCSPAGE_H
