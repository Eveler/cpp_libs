#include "mqmllibraries_plugin.h"

#include "logreader.h"
#include "Tree/treeitem.h"
#include "Tree/treemodel.h"
#include "List/list.h"

#include "mqml.h"

#include <qqml.h>


void MQMLLibrariesPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri)
  QQmlContext *context = engine->rootContext();
  context->setContextProperty( "MQML", new MQML );
}

void MQMLLibrariesPlugin::registerTypes(const char *uri)
{
    // @uri extensions.mihail.mqmllibraries
  qmlRegisterSingletonType<LogReader>( uri, 1, 0, "LogReader", logReader_Provider );

  qmlRegisterType<TreeItem>(uri, 1, 0, "TreeItem");
  qmlRegisterType<TreeModel>(uri, 1, 0, "TreeModel");

  qmlRegisterType<List>(uri, 1, 0, "List");
}


