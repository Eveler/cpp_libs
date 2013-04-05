#ifndef CONFIGURATION_P_H
#define CONFIGURATION_P_H

#include <QObject>

#include <QHash>
#include <QFileInfo>
#include <QUrl>


class Widget_Configuration;
class QMenu;
class QPluginLoader;
class QAction;
class DBCatalog_Interface;

class Configuration_P : public QObject
{
  Q_OBJECT
  friend class Widget_Configuration;


public:


signals:


public slots:


private:
  QMenu *m__MenuPlugins;
  QList<QPluginLoader *> m__Plugins;
  QHash<QAction *, DBCatalog_Interface *> m__PluginActivator;

  explicit Configuration_P( QMenu *menuPlugins, Widget_Configuration *parent );
  ~Configuration_P();

  Widget_Configuration * p_dptr() const;

  QPluginLoader * plugin( const QFileInfo &fileInfo );
  void loadPlugin( const QFileInfo &fileInfo );
  void unloadPlugin( QPluginLoader *pl );


private slots:
  void loadConfiguration();
  void saveConfiguration();

  void updatePlugins();
  void createPluginWidget();
};

#endif // CONFIGURATION_P_H
