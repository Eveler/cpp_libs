#ifndef RESULTWAYLOADER_H
#define RESULTWAYLOADER_H

#include <QObject>

#include <QtQml>


class ResultwayLoader_P;
class ResultwayInfo;

class ResultwayLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultwayLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    ResultwayLoader(QObject *parent = 0);
    ~ResultwayLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( QString filter = QString(), bool blockUI = false );

    int count() const;

    Q_INVOKABLE ResultwayInfo * newInfo();


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void countChanged();


  public slots:


  private:
    ResultwayLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ResultwayLoader)

#endif // RESULTWAYLOADER_H
