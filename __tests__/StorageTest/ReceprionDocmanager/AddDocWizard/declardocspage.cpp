#include "declardocspage.h"
#include "ui_declardocspage.h"

DeclarDocsPage::DeclarDocsPage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::DeclarDocsPage)
{
  ui->setupUi(this);

  setFinalPage( true );
}

DeclarDocsPage::~DeclarDocsPage()
{
  delete ui;
}

int DeclarDocsPage::nextId() const
{
  return -1;
}
