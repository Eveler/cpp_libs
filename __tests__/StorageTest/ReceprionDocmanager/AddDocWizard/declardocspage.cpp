#include "declardocspage.h"
#include "ui_declardocspage.h"

#include "wizard_adddoc.h"


DeclarDocsPage::DeclarDocsPage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::DeclarDocsPage)
{
  ui->setupUi(this);

  setTitle( tr( "Выбор документов из ранее прикрепленных к делу документов" ) );

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
