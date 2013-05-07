#include "dialog_newplugins.h"
#include "ui_dialog_newplugins.h"

Dialog_NewPlugins::Dialog_NewPlugins(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_NewPlugins)
{
  ui->setupUi(this);
}

Dialog_NewPlugins::~Dialog_NewPlugins()
{
  delete ui;
}

void Dialog_NewPlugins::clear()
{
  ui->listWidget->clear();
}

void Dialog_NewPlugins::addPluginName( const QString &pluginName )
{
  if ( !ui->listWidget->findItems( pluginName, Qt::MatchFixedString ).isEmpty() ) return;

  QListWidgetItem *lwi_PluginName = new QListWidgetItem( pluginName );
  lwi_PluginName->setCheckState( Qt::Checked );
  ui->listWidget->addItem( lwi_PluginName );
}

void Dialog_NewPlugins::removePluginName( const QString &pluginName )
{
  QList<QListWidgetItem *> items = ui->listWidget->findItems( pluginName, Qt::MatchFixedString );
  if ( !items.isEmpty() )
  {
    QListWidgetItem *lwi_PluginName = items.takeFirst();
    delete lwi_PluginName;
    lwi_PluginName = NULL;
  }
}

QStringList Dialog_NewPlugins::pluginNames() const
{
  QStringList result = QStringList();
  for ( int index = 0; index < ui->listWidget->count(); index++ )
    result << ui->listWidget->item( index )->text();
  return result;
}

QStringList Dialog_NewPlugins::selectedPluginNames() const
{
  QStringList result = QStringList();
  for ( int index = 0; index < ui->listWidget->count(); index++ )
    if ( ui->listWidget->item( index )->checkState() == Qt::Checked )
      result << ui->listWidget->item( index )->text();
  return result;
}

void Dialog_NewPlugins::reject()
{
  QDialog::accept();
}


void Dialog_NewPlugins::on_tBt_SelectAll_clicked()
{
  for ( int index = 0; index < ui->listWidget->count(); index++ )
    ui->listWidget->item( index )->setCheckState( Qt::Checked );
}

void Dialog_NewPlugins::on_tBt_DeselectAll_clicked()
{
  for ( int index = 0; index < ui->listWidget->count(); index++ )
    ui->listWidget->item( index )->setCheckState( Qt::Unchecked );
}
