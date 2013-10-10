#include "clientdocspage.h"
#include "ui_clientdocspage.h"

ClientDocsPage::ClientDocsPage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::ClientDocsPage)
{
  ui->setupUi(this);

  setFinalPage( true );
}

ClientDocsPage::~ClientDocsPage()
{
  delete ui;
}

int ClientDocsPage::nextId() const
{
  return -1;
}
