#include "mqmllibs_plugin.h"

#include "mdate.h"

#include <qqml.h>


void MQMLLibsPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.qmlcomponents
    qmlRegisterType<MDate>(uri, 1, 0, "MDate");
}


