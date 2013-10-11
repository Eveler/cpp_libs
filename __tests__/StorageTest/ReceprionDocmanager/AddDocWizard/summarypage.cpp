#include "summarypage.h"
#include "ui_summarypage.h"

SummaryPage::SummaryPage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::SummaryPage)
{
  ui->setupUi(this);

  setFinalPage( true );
}

SummaryPage::~SummaryPage()
{
  delete ui;
}
