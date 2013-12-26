#ifndef RECIPIENTLOADER_H
#define RECIPIENTLOADER_H

#include <QObject>

#include <QtQml>


class RecipientLoader_P;
class RecipientInfo;

class RecipientLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RecipientLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    RecipientLoader(QObject *parent = 0);
    ~RecipientLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( QString filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE RecipientInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    RecipientLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(RecipientLoader)

#endif // RECIPIENTLOADER_H
