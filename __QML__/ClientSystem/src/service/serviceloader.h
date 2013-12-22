#ifndef SERVICELOADER_H
#define SERVICELOADER_H

#include <QObject>

#include <QtQml>


class ServiceLoader_P;
class ServiceInfo;

class ServiceLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServiceLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)


  public:
    ServiceLoader(QObject *parent = 0);
    ~ServiceLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( ServiceInfo *info );


  public slots:


  private:
    ServiceLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ServiceLoader)

#endif // SERVICELOADER_H
