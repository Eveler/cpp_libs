#ifndef RESULTLOADER_H
#define RESULTLOADER_H

#include <QObject>

#include <QtQml>


class ResultLoader_P;
class ResultInfo;

class ResultLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    ResultLoader(QObject *parent = 0);
    ~ResultLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( QString filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE ResultInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    ResultLoader_P *p;
    QEventLoop *loop;


  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ResultLoader)

#endif // RESULTLOADER_H
