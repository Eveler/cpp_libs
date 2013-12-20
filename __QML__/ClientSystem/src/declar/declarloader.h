#ifndef DECLARLOADER_H
#define DECLARLOADER_H

#include <QObject>

#include <QtQml>


class DeclarLoader_P;
class DeclarInfo;

class DeclarLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    DeclarLoader(QObject *parent = 0);
    ~DeclarLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( DeclarInfo *info );


  public slots:


  private:
    DeclarLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DeclarLoader)

#endif // DECLARLOADER_H
