#include "dialog_docdetails.h"
#include "ui_dialog_docdetails.h"

#include <QPushButton>


Dialog_DocDetails::Dialog_DocDetails(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_DocDetails)
{
  ui->setupUi(this);
}

Dialog_DocDetails::~Dialog_DocDetails()
{
  delete ui;
}

MFCDocumentInfo * Dialog_DocDetails::exec( const QStringList &doctypes )
{
  ui->cBox_Doctype->setEditable( true );
  ui->lEdit_Name->setReadOnly( false );
  ui->lEdit_Series->setReadOnly( false );
  ui->lEdit_Number->setReadOnly( false );
  ui->dEdit_Date->setReadOnly( false );
  ui->dEdit_Expires->setReadOnly( false );
  ui->wgt_OC->setVisible( true );

  ui->cBox_Doctype->clear();
  ui->cBox_Doctype->addItems( doctypes );
  int currentIndex = ui->cBox_Doctype->currentIndex();
  ui->cBox_Doctype->setCurrentIndex( -1 );

  if ( currentIndex == -1 )
    check( QString(), ui->dEdit_Date->date(),
           ui->gBox_Originals->isChecked(),
           ui->spBox_OExemplars->value(),
           ui->spBox_OPages->value(),
           ui->gBox_Copies->isChecked(),
           ui->spBox_CExemplars->value(),
           ui->spBox_CPages->value() );

  if ( (QDialog::DialogCode)QDialog::exec() == QDialog::Rejected )
    return NULL;
  else
  {
    qApp->processEvents();
    QString doc_type;
    if ( ui->cBox_Doctype->currentIndex() > -1 )
      doc_type = ui->cBox_Doctype->itemText( ui->cBox_Doctype->currentIndex() );
    MFCDocumentInfo *doc = MFCDocumentInfo::instance(
                             doc_type, ui->lEdit_Name->text(),
                             ui->lEdit_Series->text(), ui->lEdit_Number->text(),
                             ui->dEdit_Date->date(), ui->dEdit_Expires->date() );
    if ( ui->gBox_Originals->isChecked() )
    {
      doc->setOriginalExemplars( ui->spBox_OExemplars->value() );
      doc->setOriginalPages( ui->spBox_OPages->value() );
    }
    if ( ui->gBox_Copies->isChecked() )
    {
      doc->setCopyExemplars( ui->spBox_CExemplars->value() );
      doc->setCopyPages( ui->spBox_CPages->value() );
    }
    return doc;
  }
}

int Dialog_DocDetails::exec( MFCDocumentInfo *doc )
{
  if ( doc == NULL ) return QDialog::Rejected;

  m__Document = doc;
  ui->cBox_Doctype->setEditable( false );
  ui->lEdit_Name->setReadOnly( true );
  ui->lEdit_Series->setReadOnly( true );
  ui->lEdit_Number->setReadOnly( true );
  ui->dEdit_Date->setReadOnly( true );
  ui->dEdit_Expires->setReadOnly( true );
  ui->wgt_OC->setVisible( false );

  ui->cBox_Doctype->clear();
  ui->cBox_Doctype->addItem( doc->type() );

  ui->lEdit_Name->setText( doc->name() );
  ui->lEdit_Series->setText( doc->series() );
  ui->lEdit_Number->setText( doc->number() );
  ui->dEdit_Date->setDate( doc->date() );
  ui->dEdit_Expires->setDate( doc->expiresDate() );

  return QDialog::exec();
}

void Dialog_DocDetails::check( QString doc_type, QDate doc_date,
                               bool isOriginals, int oExemplars, int oPages,
                               bool isCopies, int cExemplars, int cPages )
{
  QPushButton *pBt = ui->buttonBox->button( QDialogButtonBox::Ok );
  if ( pBt != NULL )
    pBt->setEnabled( !doc_type.isEmpty() && doc_date.isValid() &&
                     ( ( isOriginals && oExemplars > 0 && oPages > 0 ) ||
                       ( isCopies && cExemplars > 0 && cPages > 0 ) ) );
}

void Dialog_DocDetails::on_cBox_Doctype_currentIndexChanged(int index)
{
  QString doc_type;
  if ( index > -1 ) doc_type = ui->cBox_Doctype->itemText( index );

  check( doc_type, ui->dEdit_Date->date(),
         ui->gBox_Originals->isChecked(),
         ui->spBox_OExemplars->value(),
         ui->spBox_OPages->value(),
         ui->gBox_Copies->isChecked(),
         ui->spBox_CExemplars->value(),
         ui->spBox_CPages->value() );
}

void Dialog_DocDetails::on_dEdit_Date_dateChanged(const QDate &date)
{
  QString doc_type;
  if ( ui->cBox_Doctype->currentIndex() > -1 )
    doc_type = ui->cBox_Doctype->itemText( ui->cBox_Doctype->currentIndex() );

  check( doc_type, date,
         ui->gBox_Originals->isChecked(),
         ui->spBox_OExemplars->value(),
         ui->spBox_OPages->value(),
         ui->gBox_Copies->isChecked(),
         ui->spBox_CExemplars->value(),
         ui->spBox_CPages->value() );
}

void Dialog_DocDetails::on_gBox_Originals_toggled(bool arg1)
{
  QString doc_type;
  if ( ui->cBox_Doctype->currentIndex() > -1 )
    doc_type = ui->cBox_Doctype->itemText( ui->cBox_Doctype->currentIndex() );

  check( doc_type, ui->dEdit_Date->date(),
         arg1, ui->spBox_OExemplars->value(),
         ui->spBox_OPages->value(),
         ui->gBox_Copies->isChecked(),
         ui->spBox_CExemplars->value(),
         ui->spBox_CPages->value() );

//  if ( arg1 ) ui->gBox_Copies->setChecked( false );
}

void Dialog_DocDetails::on_gBox_Copies_toggled(bool arg1)
{
  QString doc_type;
  if ( ui->cBox_Doctype->currentIndex() > -1 )
    doc_type = ui->cBox_Doctype->itemText( ui->cBox_Doctype->currentIndex() );

  check( doc_type, ui->dEdit_Date->date(),
         ui->gBox_Originals->isChecked(),
         ui->spBox_OExemplars->value(),
         ui->spBox_OPages->value(),
         arg1, ui->spBox_CExemplars->value(),
         ui->spBox_CPages->value() );

//  if ( arg1 ) ui->gBox_Originals->setChecked( false );
}
