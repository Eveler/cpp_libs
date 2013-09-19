#include <QAbstractButton>
#include "documentmetadata.h"
#include "ui_documentmetadata.h"

DocumentMetadata::DocumentMetadata(MFCDocument *doc, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DocumentMetadata),
  document(doc)
{
  ui->setupUi(this);

  if(doc->havePages()) ui->spBox_Pages->setValue(doc->pages()->count());
  else pages=ui->spBox_Pages->value();
  original_number=ui->spBox_OriginalNumber->value();
  copy_number=ui->spBox_CopyNumber->value();
  QDialogButtonBox *bb=ui->buttonBox;
  foreach(QAbstractButton *b,bb->buttons()){
    if(bb->buttonRole(b)==QDialogButtonBox::AcceptRole){
      b->setText(tr("Готово"));
    }
    if(bb->buttonRole(b)==QDialogButtonBox::RejectRole){
      b->setText(tr("Отмена"));
    }
    b->setDisabled(true);
  }
}

DocumentMetadata::~DocumentMetadata()
{
  delete ui;
}

void DocumentMetadata::setCancelEnabled(bool enabled)
{
  QDialogButtonBox *bb=ui->buttonBox;
  foreach(QAbstractButton *b,bb->buttons()){
    if(bb->buttonRole(b)==QDialogButtonBox::RejectRole){
      b->setEnabled(enabled);
    }
  }
}

void DocumentMetadata::setAcceptEnabled(bool enabled)
{
  QDialogButtonBox *bb=ui->buttonBox;
  foreach(QAbstractButton *b,bb->buttons()){
    if(bb->buttonRole(b)==QDialogButtonBox::AcceptRole){
      b->setEnabled(enabled);
    }
  }
}

void DocumentMetadata::on_spBox_Pages_valueChanged(int arg1)
{
  pages=arg1;
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_spBox_OriginalNumber_valueChanged(int arg1)
{
  original_number=arg1;
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_spBox_CopyNumber_valueChanged(int arg1)
{
  copy_number=arg1;
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_gBox_Original_toggled(bool arg1)
{
  if(!arg1) ui->spBox_OriginalNumber->setValue(0);
  else if(original_number<=0) ui->spBox_OriginalNumber->setValue(1);
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_gBox_Copy_toggled(bool arg1)
{
  if(!arg1) ui->spBox_CopyNumber->setValue(0);
  else if(copy_number<=0) ui->spBox_CopyNumber->setValue(1);
  setAcceptEnabled(canAccept());
}

bool DocumentMetadata::canAccept() const
{
  return ((ui->gBox_Original->isChecked() && ui->spBox_OriginalNumber->value()>0)
      || (ui->gBox_Copy->isChecked() && ui->spBox_CopyNumber->value()>0))
      && ui->spBox_Pages->value()>0;
}

void DocumentMetadata::on_buttonBox_accepted()
{
  if(pages>0) document->setProperty(tr("Страниц").toLocal8Bit(),pages);
  if(original_number>0)
    document->setProperty(tr("Оригиналов").toLocal8Bit(),original_number);
  if(copy_number>0) document->setProperty(tr("Копий").toLocal8Bit(),copy_number);
}
