#ifndef CLIENTLOADER_H
#define CLIENTLOADER_H

#include <QObject>

#include <QtQml>


class ClientLoader_P;
class ClientInfo;

class ClientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ClientLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    ClientLoader(QObject *parent = 0);
    ~ClientLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( ClientInfo *info );


  public slots:


  private:
    ClientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ClientLoader)

#endif // CLIENTLOADER_H
