#ifndef DIALOG_NEWPLUGINS_H
#define DIALOG_NEWPLUGINS_H

#include <QDialog>


namespace Ui {
class Dialog_NewPlugins;
}

class Dialog_NewPlugins : public QDialog
{
  Q_OBJECT


public:
  explicit Dialog_NewPlugins(QWidget *parent = 0);
  ~Dialog_NewPlugins();

  void clear();
  void addPluginName( const QString &pluginName );
  void removePluginName( const QString &pluginName );
  QStringList pluginNames() const;

  QStringList selectedPluginNames() const;


public slots:
  void reject();


private:
  Ui::Dialog_NewPlugins *ui;


private slots:
  void on_tBt_SelectAll_clicked();
  void on_tBt_DeselectAll_clicked();
};

#endif // DIALOG_NEWPLUGINS_H
