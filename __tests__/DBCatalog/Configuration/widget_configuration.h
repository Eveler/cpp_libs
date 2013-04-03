#ifndef WIDGET_CONFIGURATION_H
#define WIDGET_CONFIGURATION_H

#include <QWidget>


namespace Ui {
class Widget_Configuration;
}

class Configuration_P;
class QMenu;

class Widget_Configuration : public QWidget
{
  Q_OBJECT
  friend class Configuration_P;


public:
  explicit Widget_Configuration( QMenu *menuPlugins, QWidget *parent = 0 );
  ~Widget_Configuration();


public slots:
  void updatePlugins();


signals:
  void pluginWidgetCreated( QWidget *widget );


private:
  Ui::Widget_Configuration *ui;

  Configuration_P *p;

  void afterPluginWidgetCreated( QWidget *widget );
};

#endif // WIDGET_CONFIGURATION_H
