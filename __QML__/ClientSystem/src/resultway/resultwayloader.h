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


  public:
    ResultwayLoader(QObject *parent = 0);
    ~ResultwayLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( ResultwayInfo *info );


  public slots:


  private:
    ResultwayLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ResultwayLoader)

#endif // RESULTWAYLOADER_H
