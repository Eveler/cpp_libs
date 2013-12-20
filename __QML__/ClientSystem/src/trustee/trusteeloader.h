#ifndef TRUSTEELOADER_H
#define TRUSTEELOADER_H

#include <QObject>

#include <QtQml>


class TrusteeLoader_P;
class TrusteeInfo;

class TrusteeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TrusteeLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    TrusteeLoader(QObject *parent = 0);
    ~TrusteeLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( TrusteeInfo *info );


  public slots:


  private:
    TrusteeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(TrusteeLoader)

#endif // TRUSTEELOADER_H
