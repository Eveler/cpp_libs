#include "mqmllibs_plugin.h"

#include "mdate.h"
#include "melectrodoc.h"
#include "popuppanel.h"

#include <qqml.h>


void MQMLLibsPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.qmlcomponents
    qmlRegisterType<MDate>(uri, 1, 0, "MDate");
    qmlRegisterType<MElectroDoc>(uri, 1, 0, "MElectroDoc");
    qmlRegisterType<PopupPanel>(uri, 1, 0, "PopupPanel");
}


