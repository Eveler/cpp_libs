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


  public:
    DeclarClientLoader(QObject *parent = 0);
    ~DeclarClientLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( DeclarClientInfo *info );


  public slots:


  private:
    DeclarClientLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DeclarClientLoader)

#endif // declarCLIENTLOADER_H
