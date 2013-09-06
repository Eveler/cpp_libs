#ifndef CLIENTSYSTEM_PLUGIN_H
#define CLIENTSYSTEM_PLUGIN_H

#include <QQmlExtensionPlugin>

class ClientSystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
    
public:
    void registerTypes(const char *uri);
};

#endif // CLIENTSYSTEM_PLUGIN_H

