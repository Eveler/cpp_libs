#ifndef CLIENTSYSTEM_PLUGIN_H
#define CLIENTSYSTEM_PLUGIN_H

#include <QQmlExtensionPlugin>
#include <QtQml>


class ClientSystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
    

  public:
    void initializeEngine(QQmlEngine *engine, const char *uri);
    void registerTypes(const char *uri);


  private:

};

#endif // CLIENTSYSTEM_PLUGIN_H

