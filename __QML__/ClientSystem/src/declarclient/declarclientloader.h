#ifndef declarCLIENTLOADER_H
#define declarCLIENTLOADER_H

#include <QObject>

#include <QtQml>


class DeclarClientLoader_P;
class DeclarClientInfo;

class DeclarClientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarClientLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)


  public:
    DeclarClientLoader(QObject *parent = 0);
    ~DeclarClientLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( DeclarClientInfo *info );


  public slots:


  private:
    DeclarClientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DeclarClientLoader)

#endif // declarCLIENTLOADER_H
