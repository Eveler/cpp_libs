#include "mqmllibraries_plugin.h"

#include "logreader.h"
#include "Tree/treeitem.h"
#include "Tree/treemodel.h"

#include <qqml.h>

void MQMLLibrariesPlugin::registerTypes(const char *uri)
{
    // @uri Extesions.MQMLLibraries
  qmlRegisterSingletonType<LogReader>( uri, 1, 0, "LogReader", logReader_Provider );
  qmlRegisterType<TreeItem>(uri, 1, 0, "TreeItem");
  qmlRegisterType<TreeModel>(uri, 1, 0, "TreeModel");
}


