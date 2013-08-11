#ifndef MQMLPLUGINS_H
#define MQMLPLUGINS_H

#include <QQuickItem>

class MQMLPlugins : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MQMLPlugins)
    
public:
    MQMLPlugins(QQuickItem *parent = 0);
    ~MQMLPlugins();
};

QML_DECLARE_TYPE(MQMLPlugins)

#endif // MQMLPLUGINS_H

