#include "mqmlplugins_plugin.h"
#include "mqmlplugins.h"

#include <qqml.h>

void MQMLPluginsPlugin::registerTypes(const char *uri)
{
    // @uri mqmlcomponents
    qmlRegisterType<MQMLPlugins>(uri, 1, 0, "MQMLPlugins");
}


