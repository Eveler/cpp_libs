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


  public:
    ResultLoader(QObject *parent = 0);
    ~ResultLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( ResultInfo *info );


  public slots:


  private:
    ResultLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(ResultLoader)

#endif // RESULTLOADER_H
