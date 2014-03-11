#ifndef MDATABASE_H
#define MDATABASE_H

#include <QQuickItem>

#include "export/mdataset_export_lib.h"


class EXPORT_MDATASET MDatabase : public QObject
{
    Q_OBJECT


  public:
    explicit MDatabase( QObject *parent = NULL );
    ~MDatabase();

    Q_INVOKABLE static void createDatabase( const QString &driverName, const QString &connectionName, const QString &hostName, int port,
                                            const QString &databaseName, const QString &userName, const QString &password );
};

#endif // MDATABASE_H
