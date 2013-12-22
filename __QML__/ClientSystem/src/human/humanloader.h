#ifndef HUMANLOADER_H
#define HUMANLOADER_H

#include <QObject>

#include <QtQml>


class HumanLoader_P;
class HumanInfo;

class HumanLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HumanLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)


  public:
    HumanLoader(QObject *parent = 0);
    ~HumanLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( HumanInfo *info );


  public slots:


  private:
    HumanLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(HumanLoader)

#endif // HUMANLOADER_H
