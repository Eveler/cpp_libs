#include "mdatedialog.h"
#include "ui_mdatedialog.h"

MDateDialog::MDateDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MDateDialog)
{
  ui->setupUi(this);
}

MDateDialog::~MDateDialog()
{
  delete ui;
}

void MDateDialog::setDisplayFormat( const QString &displayFormat )
{
  ui->dateTimeEdit->setDisplayFormat( displayFormat );
}

QString MDateDialog::displayFormat() const
{
  return ui->dateTimeEdit->displayFormat();
}

void MDateDialog::setText( const QString &text )
{
  ui->label_2->setText( text );
}

QString MDateDialog::text() const
{
  return ui->label_2->text();
}

QDateTime MDateDialog::dateTime() const
{
  return ui->dateTimeEdit->dateTime();
}
