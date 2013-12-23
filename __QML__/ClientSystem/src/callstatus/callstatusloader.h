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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    CallstatusLoader(QObject *parent = 0);
    ~CallstatusLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( bool blockUI = false );
    Q_INVOKABLE bool load( QVariant identifier, bool blockUI = false );

    int count() const;

    Q_INVOKABLE CallstatusInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    CallstatusLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(CallstatusLoader)

#endif // CALLSTATUSLOADER_H
