#ifndef MQMLPLUGINS_PLUGIN_H
#define MQMLPLUGINS_PLUGIN_H

#include <QQmlExtensionPlugin>

class MQMLPluginsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // MQMLPLUGINS_PLUGIN_H

