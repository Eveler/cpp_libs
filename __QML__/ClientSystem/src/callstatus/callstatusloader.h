#ifndef CALLSTATUSLOADER_H
#define CALLSTATUSLOADER_H

#include <QObject>

#include <QtQml>


class CallstatusLoader_P;
class CallstatusInfo;

class CallstatusLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CallstatusLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    CallstatusLoader(QObject *parent = 0);
    ~CallstatusLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( bool blockUI = false );
    Q_INVOKABLE bool load( QVariant identifier, bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( CallstatusInfo *info );


  public slots:


  private:
    CallstatusLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(CallstatusLoader)

#endif // CALLSTATUSLOADER_H
