#include "qmldocumentsystem_plugin.h"

#include "qmldocument.h"
#include "qmldocumentloader.h"

#include <qqml.h>

void QMLDocumentSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.qmldocumentsystem
    qmlRegisterType<QMLDocument>(uri, 1, 0, "QMLDocument");
    qmlRegisterType<QMLDocumentLoader>(uri, 1, 0, "QMLDocumentLoader");
}


