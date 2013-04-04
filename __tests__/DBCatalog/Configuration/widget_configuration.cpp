#include "widget_configuration.h"
#include "ui_widget_configuration.h"

#include "configuration_p.h"


Widget_Configuration::Widget_Configuration( QMenu *menuPlugins, QWidget *parent ) :
  QDialog(parent),
  ui(new Ui::Widget_Configuration)
{
  ui->setupUi(this);

  p = new Configuration_P( menuPlugins, this );
  connect( ui->tBt_Apply, SIGNAL(clicked()), p, SLOT(saveConfiguration()) );

  ui->listWidget->setCurrentRow( 0 );
}

Widget_Configuration::~Widget_Configuration()
{
  delete p;
  p = NULL;

  delete ui;
  ui = NULL;
}

void Widget_Configuration::reject()
{
  p->loadConfiguration();
  QDialog::reject();
}

void Widget_Configuration::afterPluginWidgetCreated( QWidget *widget )
{
  emit pluginWidgetCreated( widget );
}

void Widget_Configuration::on_listWidget_currentRowChanged(int currentRow)
{
  if ( currentRow == 0 )
    ui->stackedWidget->setCurrentWidget( ui->page_Main );
  else if ( currentRow == 1 )
    ui->stackedWidget->setCurrentWidget( ui->page_Tools );
}
