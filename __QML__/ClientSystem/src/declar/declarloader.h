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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    DeclarLoader(QObject *parent = 0);
    ~DeclarLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( QString filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE DeclarInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    DeclarLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DeclarLoader)

#endif // DECLARLOADER_H
