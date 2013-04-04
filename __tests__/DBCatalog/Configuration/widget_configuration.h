#ifndef WIDGET_CONFIGURATION_H
#define WIDGET_CONFIGURATION_H

#include <QDialog>


namespace Ui {
class Widget_Configuration;
}

class Configuration_P;
class QMenu;

class Widget_Configuration : public QDialog
{
  Q_OBJECT
  friend class Configuration_P;


public:
  explicit Widget_Configuration( QMenu *menuPlugins, QWidget *parent = 0 );
  ~Widget_Configuration();


public slots:
  void reject();

signals:
  void pluginWidgetCreated( QWidget *widget );


private:
  Ui::Widget_Configuration *ui;

  Configuration_P *p;

  void afterPluginWidgetCreated( QWidget *widget );


private slots:
  void on_listWidget_currentRowChanged(int currentRow);
};

#endif // WIDGET_CONFIGURATION_H
