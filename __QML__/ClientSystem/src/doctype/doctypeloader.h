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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    DoctypeLoader(QObject *parent = 0);
    ~DoctypeLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( QString filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE DoctypeInfo *newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    DoctypeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(DoctypeLoader)

#endif // DOCTYPELOADER_H
