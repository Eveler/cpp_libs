#include "minputdialog.h"
#include "ui_minputdialog.h"

#include <QPushButton>


MInputDialog::MInputDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MInputDialog)
{
  ui->setupUi(this);
}

MInputDialog::~MInputDialog()
{
  delete ui;
}

void MInputDialog::setLabel( const QString &label )
{
  ui->label->setText( label );
}

QString MInputDialog::label() const
{
  return ui->label->text();
}

void MInputDialog::setComboBoxItems( const QStringList &items )
{
  ui->comboBox->clear();
  ui->comboBox->addItems( items );
  ui->comboBox->setCurrentIndex( -1 );
}

QStringList MInputDialog::comboBoxItems() const
{
  QStringList result;
  for ( int iIdx = 0; iIdx < ui->comboBox->count(); iIdx++ )
    result << ui->comboBox->itemText( iIdx );
  return result;
}

void MInputDialog::setInputText( const QString &text )
{
  int res = ui->comboBox->findText( text );
  ui->comboBox->setCurrentIndex( res );
}

QString MInputDialog::inputText() const
{
  if ( ui->comboBox->currentIndex() == -1 ) return QString();
  return ui->comboBox->itemText( ui->comboBox->currentIndex() );
}

void MInputDialog::setComboBoxEditable( bool editable )
{
  ui->comboBox->setEditable( editable );
}

bool MInputDialog::isComboBoxEditable() const
{
  return ui->comboBox->isEditable();
}

QString MInputDialog::getItem( QWidget *parent, const QString &title,
                               const QString &label, const QStringList &items,
                               int current, bool editable, Qt::WindowFlags flags )
{
  MInputDialog inputDialog;
  inputDialog.setParent( parent );
  inputDialog.setWindowTitle( title );
  inputDialog.setLabel( label );
  inputDialog.setComboBoxItems( items );
  inputDialog.setInputText( items.value( current ) );
  inputDialog.setComboBoxEditable( editable );
  inputDialog.setWindowFlags( flags );
  if ( inputDialog.exec() == QDialog::Rejected ) return QString();
  return inputDialog.inputText();
}

void MInputDialog::on_comboBox_currentIndexChanged(int index)
{
  ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( index > -1 );
  if ( index < 0 ) return;
  ui->comboBox->setMinimumHeight(
        ui->comboBox->view()->visualRect(
          ui->comboBox->view()->model()->index( index, 0 ) ).height()+5 );
}
