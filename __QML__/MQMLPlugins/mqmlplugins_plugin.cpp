#include "mqmlplugins_plugin.h"
#include "mqmlplugins.h"

#include <qqml.h>

void MQMLPluginsPlugin::registerTypes(const char *uri)
{
    // @uri mqmlcomponents
    Q_ASSERT(uri == QLatin1String("mqmlcomponents"));
    qmlRegisterType<MQMLPlugins>(uri, 1, 0, "MQMLPlugins");
}


