#ifndef CLIENTSYSTEMSOURCES_PLUGIN_H
#define CLIENTSYSTEMSOURCES_PLUGIN_H

#include <QQmlExtensionPlugin>

class ClientSystemSourcesPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

  public:
    void registerTypes(const char *uri);
};

#endif // CLIENTSYSTEMSOURCES_PLUGIN_H

