#ifndef CLIENTDOCSPAGE_H
#define CLIENTDOCSPAGE_H

#include <QWizardPage>


namespace Ui {
  class ClientDocsPage;
}

class ClientDocsPage : public QWizardPage
{
    Q_OBJECT


  public:
    explicit ClientDocsPage(QWidget *parent = 0);
    ~ClientDocsPage();

    int nextId() const;


  private:
    Ui::ClientDocsPage *ui;
};

#endif // CLIENTDOCSPAGE_H
