#ifndef DECLARDOCSPAGE_H
#define DECLARDOCSPAGE_H

#include <QWizardPage>


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


  private:
    Ui::DeclarDocsPage *ui;
};

#endif // DECLARDOCSPAGE_H
