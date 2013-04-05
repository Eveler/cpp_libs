#ifndef WIDGET_PLUGINSSOURCELOADER_H
#define WIDGET_PLUGINSSOURCELOADER_H

#include <QWidget>


namespace Ui {
class Widget_PluginsSourceLoader;
}

class PluginsSourceLoader_P;

class Widget_PluginsSourceLoader : public QWidget
{
  Q_OBJECT
  friend class PluginsSourceLoader_P;


public:
  explicit Widget_PluginsSourceLoader(QWidget *parent = 0);
  ~Widget_PluginsSourceLoader();

  void setPluginsSourceList( const QStringList &sourceList );
  QStringList pluginsSourceList() const;

  const QStringList & plugins() const;
  const QByteArray & pluginHash( const QString &plugin ) const;


signals:
  void newPlugins( QHash<QString, QByteArray> pluginsHash );


private:
  Ui::Widget_PluginsSourceLoader *ui;

  PluginsSourceLoader_P *p;


private slots:
  void on_tBt_AddSource_clicked();
};

#endif // WIDGET_PLUGINSSOURCELOADER_H
