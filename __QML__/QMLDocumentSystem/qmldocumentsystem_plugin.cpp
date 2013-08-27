#include "qmldocumentsystem_plugin.h"

#include "qmldocument.h"
#include "qmldocumentloader.h"
#include "qmldocumentpageprovider.h"

#include <qqml.h>

void QMLDocumentSystemPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
    engine->addImageProvider( QString( "qmldocumentprovider" ),
                              new QMLDocumentPageProvider );
}

void QMLDocumentSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.mihail.qmldocumentsystem
    qmlRegisterType<QMLDocument>(uri, 1, 0, "QMLDocument");
    qmlRegisterType<QMLDocumentLoader>(uri, 1, 0, "QMLDocumentLoader");
}


