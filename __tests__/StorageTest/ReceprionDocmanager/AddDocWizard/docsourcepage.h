#ifndef DOCSOURCEPAGE_H
#define DOCSOURCEPAGE_H

#include <QWizardPage>


namespace Ui {
  class DocSourcePage;
}

class DocSourcePage : public QWizardPage
{
    Q_OBJECT


  public:
    explicit DocSourcePage(QWidget *parent = 0);
    ~DocSourcePage();

    int nextId() const;

    bool isComplete() const;


  private:
    Ui::DocSourcePage *ui;


  private slots:
    void sourceChanged( bool changed );
};

#endif // DOCSOURCEPAGE_H
