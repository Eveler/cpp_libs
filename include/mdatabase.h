#ifndef MDATABASE_H
#define MDATABASE_H

#include <QQuickItem>

#include "export/mdataset_export_lib.h"


class QReadWriteLock;
class QSqlQuery;

class EXPORT_MDATASET MDatabase : public QObject
{
    Q_OBJECT


  public:
    ~MDatabase();

    static MDatabase * instance( QObject *parent = NULL );
    Q_INVOKABLE void createDatabase( const QString &driverName, const QString &connectionName, const QString &hostName, int port,
                                     const QString &databaseName, const QString &userName, const QString &password );
    QSqlQuery * getQuery( const QString &queryText, const QString &connectionName );


  private:
    static MDatabase *m__Instance;
    QReadWriteLock *m__Locker;

    explicit MDatabase( QObject *parent );
};

#endif // MDATABASE_H
