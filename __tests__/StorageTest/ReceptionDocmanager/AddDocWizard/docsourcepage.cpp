#include "docsourcepage.h"
#include "ui_docsourcepage.h"

#include "wizard_adddoc.h"

#include <QDebug>


DocSourcePage::DocSourcePage(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::DocSourcePage)
{
  ui->setupUi(this);

  setTitle( tr( "Вас приветствует Мастер добавления документов" ) );

  connect( ui->rBt_CreateDocs, SIGNAL(toggled(bool)), SLOT(sourceChanged(bool)) );
  connect( ui->rBt_ClientDocs, SIGNAL(toggled(bool)), SLOT(sourceChanged(bool)) );
  connect( ui->rBt_DeclarDocs, SIGNAL(toggled(bool)), SLOT(sourceChanged(bool)) );

  registerField( "isCreateDocs", ui->rBt_CreateDocs );
  registerField( "isClientDocs", ui->rBt_ClientDocs );
  registerField( "isDeclarDocs", ui->rBt_DeclarDocs );
}

DocSourcePage::~DocSourcePage()
{
  delete ui;
}

int DocSourcePage::nextId() const
{
  int result = -1;

  if ( ui->rBt_CreateDocs->isChecked() ) result = Wizard_AddDoc::Page_CreateDocs;
  else if ( ui->rBt_ClientDocs->isChecked() ) result = Wizard_AddDoc::Page_ClientDocs;
  else result = Wizard_AddDoc::Page_DeclarDocs;

  return result;
}

bool DocSourcePage::isComplete() const
{
  if ( ui->rBt_CreateDocs->isChecked() ) return true;
  if ( ui->rBt_ClientDocs->isChecked() ) return true;
  if ( ui->rBt_DeclarDocs->isChecked() ) return true;
  return false;
}

void DocSourcePage::sourceChanged( bool changed )
{
  if ( !changed ) return;

  emit completeChanged();
  wizard()->next();
}
