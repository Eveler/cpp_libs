#ifndef MAKCDATASET_PLUGIN_H
#define MAKCDATASET_PLUGIN_H

#include <QQmlExtensionPlugin>


class MAKCDatasetPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")


  public:
    void initializeEngine( QQmlEngine *engine, const char *uri );
    void registerTypes( const char *uri );
};

#endif // MAKCDATASET_PLUGIN_H

