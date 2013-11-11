#include "minputdialog.h"
#include "ui_minputdialog.h"

#include <QPushButton>


MInputDialog::MInputDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MInputDialog)
{
  ui->setupUi(this);

  setItemView( ComboBoxView );
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

void MInputDialog::setItemView( ItemView itemView )
{
  m__ItemView = itemView;
  bool isComboBox = ( m__ItemView == ComboBoxView );
  ui->comboBox->setVisible( isComboBox );
  ui->wgt_Spacer->setVisible( isComboBox );
  ui->listWidget->setVisible( !isComboBox );
  ui->wgt_Select->setVisible( !isComboBox );
}

MInputDialog::ItemView MInputDialog::itemView() const
{
  return m__ItemView;
}

void MInputDialog::setComboBoxItems( const QStringList &items )
{
  if ( m__ItemView == ComboBoxView )
  {
    ui->comboBox->clear();
    ui->comboBox->addItems( items );
    ui->comboBox->setCurrentIndex( -1 );
  }
  else
  {
    ui->listWidget->clear();
    foreach ( QString item, items )
    {
      QListWidgetItem *lwi = new QListWidgetItem( item );
      lwi->setCheckState( Qt::Unchecked );
      ui->listWidget->addItem( lwi );
    }
  }
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

QStringList MInputDialog::inputText() const
{
  if ( m__ItemView == ComboBoxView )
  {
    if ( ui->comboBox->currentIndex() == -1 ) return QStringList();
    return QStringList() << ui->comboBox->itemText( ui->comboBox->currentIndex() );
  }
  else
  {
    QStringList result;
    for ( int iIdx = 0; iIdx < ui->listWidget->count(); iIdx++ )
    {
      QListWidgetItem *lwi = ui->listWidget->item( iIdx );
      if ( lwi->checkState() == Qt::Checked )
        result << ui->listWidget->item( iIdx )->text();
    }
    return result;
  }
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
  inputDialog.resize( inputDialog.width(), 150 );
  QString result;
  if ( inputDialog.exec() == QDialog::Rejected ) return result;
  result = inputDialog.inputText().first();
  return result;
}

QStringList MInputDialog::getItems( QWidget *parent, const QString &title,
                                    const QString &label, const QStringList &items,
                                    Qt::WindowFlags flags )
{
  MInputDialog inputDialog;
  inputDialog.setParent( parent );
  inputDialog.setWindowTitle( title );
  inputDialog.setLabel( label );
  inputDialog.setItemView( ListView );
  inputDialog.setComboBoxItems( items );
  inputDialog.setWindowFlags( flags );
  inputDialog.resize( inputDialog.width(), 400 );
  if ( inputDialog.exec() == QDialog::Rejected ) return QStringList();
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

void MInputDialog::on_tBt_SelectAll_clicked()
{
  for ( int iIdx = 0; iIdx < ui->listWidget->count(); iIdx++ )
    ui->listWidget->item( iIdx )->setCheckState( Qt::Checked );
}

void MInputDialog::on_tBt_DeselectAll_clicked()
{
  for ( int iIdx = 0; iIdx < ui->listWidget->count(); iIdx++ )
    ui->listWidget->item( iIdx )->setCheckState( Qt::Unchecked );
}
