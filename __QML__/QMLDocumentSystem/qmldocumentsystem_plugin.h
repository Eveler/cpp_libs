#ifndef QMLDOCUMENTSYSTEM_PLUGIN_H
#define QMLDOCUMENTSYSTEM_PLUGIN_H

#include <QQmlExtensionPlugin>

class QMLDocumentSystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void initializeEngine( QQmlEngine *engine, const char *uri );
    void registerTypes(const char *uri);
};

#endif // QMLDOCUMENTSYSTEM_PLUGIN_H

