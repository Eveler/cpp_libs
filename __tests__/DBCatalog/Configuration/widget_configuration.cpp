#include "widget_configuration.h"
#include "ui_widget_configuration.h"

#include "configuration_p.h"


Widget_Configuration::Widget_Configuration( QMenu *menuPlugins, QWidget *parent ) :
  QWidget(parent),
  ui(new Ui::Widget_Configuration)
{
  ui->setupUi(this);

  p = new Configuration_P( menuPlugins, this );
}

Widget_Configuration::~Widget_Configuration()
{
  delete ui;
}

void Widget_Configuration::updatePlugins()
{
  p->updatePlugins();
}

void Widget_Configuration::afterPluginWidgetCreated( QWidget *widget )
{
  emit pluginWidgetCreated( widget );
}
