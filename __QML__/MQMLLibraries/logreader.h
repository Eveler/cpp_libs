#ifndef LOGREADER_H
#define LOGREADER_H

#include <QQuickItem>

#include "Tree/treeitem.h"

#include <QtQml>


class LogReader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LogReader)

  public:
    LogReader( QObject *parent = NULL );
    ~LogReader();

    Q_INVOKABLE QList<TreeItem *> load( const QString &filePath ) const;
};

QML_DECLARE_TYPE(LogReader)

static QObject * logReader_Provider( QQmlEngine *engine, QJSEngine *scriptEngine )
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new LogReader();
}

#endif // LOGREADER_H

