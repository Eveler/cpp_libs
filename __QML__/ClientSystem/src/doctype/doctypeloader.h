#ifndef DOCTYPELOADER_H
#define DOCTYPELOADER_H

#include <QObject>

#include <QtQml>


class DoctypeLoader_P;
class DoctypeInfo;

class DoctypeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DoctypeLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    DoctypeLoader(QObject *parent = 0);
    ~DoctypeLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( DoctypeInfo *info );


  public slots:


  private:
    DoctypeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DoctypeLoader)

#endif // DOCTYPELOADER_H
