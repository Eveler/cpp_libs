#include "ui_mlogindialog.h"

#include "mlogindialog_p.h"


MLoginDialog::MLoginDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MLoginDialog)
{
  ui->setupUi(this);

  p = new MLoginDialog_P( this );
}

MLoginDialog::~MLoginDialog()
{
  delete p;
  p = NULL;

  delete ui;
  ui = NULL;
}

void MLoginDialog::setNames( const QStringList &names )
{
  p->m__Names = names;

  ui->comboBox->clear();
  ui->lineEdit->clear();

  ui->comboBox->addItems( p->m__Names );
}

const QStringList & MLoginDialog::names() const
{
  return p->m__Names;
}

void MLoginDialog::setNameEditable( bool editable )
{
  ui->comboBox->setEditable( editable );
}

bool MLoginDialog::isNameEditable() const
{
  return ui->comboBox->isEditable();
}

QString MLoginDialog::selectedName() const
{
  return ui->comboBox->currentText();
}

QString MLoginDialog::selectedPassword() const
{
  return ui->lineEdit->text();
}
