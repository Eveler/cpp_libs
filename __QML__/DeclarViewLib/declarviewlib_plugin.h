#ifndef DECLARVIEWLIB_PLUGIN_H
#define DECLARVIEWLIB_PLUGIN_H

#include <QQmlExtensionPlugin>

class DeclarViewLibPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

  public:
    void registerTypes(const char *uri);
};

#endif // DECLARVIEWLIB_PLUGIN_H

