#include <QAbstractButton>
#include "documentmetadata.h"
#include "ui_documentmetadata.h"

DocumentMetadata::DocumentMetadata(MFCDocument *doc, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DocumentMetadata),
  document(doc)
{
  ui->setupUi(this);

  if(doc->havePages()){
    setOriginalPages(doc->pages()->count());
    setCopyPages(doc->pages()->count());
  }else{
    original_pages=ui->spBox_OriginalPages->value();
    copy_pages=ui->spBox_CopyPages->value();
  }
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

void DocumentMetadata::setOriginalPages(int p)
{
  ui->spBox_OriginalPages->setValue(p);
}

void DocumentMetadata::setCopyPages(int p)
{
  ui->spBox_CopyPages->setValue(p);
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
  else{
    ui->spBox_OriginalNumber->setFocus();
    if(original_number<=0) ui->spBox_OriginalNumber->setValue(1);
  }
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_gBox_Copy_toggled(bool arg1)
{
  if(!arg1) ui->spBox_CopyNumber->setValue(0);
  else{
    ui->spBox_CopyNumber->setFocus();
    if(copy_number<=0) ui->spBox_CopyNumber->setValue(1);
  }
  setAcceptEnabled(canAccept());
}

bool DocumentMetadata::canAccept() const
{
  return ((ui->gBox_Original->isChecked() && ui->spBox_OriginalNumber->value()>0)
      || (ui->gBox_Copy->isChecked() && ui->spBox_CopyNumber->value()>0))
      && ui->spBox_OriginalPages->value()>0 && ui->spBox_CopyPages->value()>0;
}

void DocumentMetadata::on_buttonBox_accepted()
{
  if(original_number!=ui->spBox_OriginalNumber->value())
    original_number=ui->spBox_OriginalNumber->value();
  if(original_pages!=ui->spBox_OriginalPages->value())
    original_pages=ui->spBox_OriginalPages->value();
  if(copy_number!=ui->spBox_CopyNumber->value())
    copy_number=ui->spBox_CopyNumber->value();
  if(copy_pages!=ui->spBox_CopyPages->value())
    copy_pages=ui->spBox_CopyPages->value();

  if(original_pages>0)
    document->setProperty(tr("Листов_оригинала").toLocal8Bit(),original_pages);
  if(copy_pages>0)
    document->setProperty(tr("Листов_копии").toLocal8Bit(),copy_pages);
  if(original_number>0)
    document->setProperty(tr("Оригиналов").toLocal8Bit(),original_number);
  if(copy_number>0)
    document->setProperty(tr("Копий").toLocal8Bit(),copy_number);
}

void DocumentMetadata::on_spBox_OriginalPages_valueChanged(int arg1)
{
  original_pages=arg1;
  setAcceptEnabled(canAccept());
}

void DocumentMetadata::on_spBox_CopyPages_valueChanged(int arg1)
{
  copy_pages=arg1;
  setAcceptEnabled(canAccept());
}
