#ifndef ASSESSMENTTYPELOADER_H
#define ASSESSMENTTYPELOADER_H

#include <QObject>

#include <QtQml>


class AssessmenttypeLoader_P;
class AssessmenttypeInfo;

class AssessmenttypeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmenttypeLoader)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString connectionName READ connectionName
               WRITE setConnectionName NOTIFY connectionNameChanged)


  public:
    AssessmenttypeLoader(QObject *parent = 0);
    ~AssessmenttypeLoader();

    Q_INVOKABLE QString lastError() const;

    const QString & connectionName() const;
    bool setConnectionName( const QString &connectionName );

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );


  signals:
    void lastErrorChanged();
    void connectionNameChanged() const;
    void started();
    void finished();
    void newInfo( AssessmenttypeInfo *info );


  public slots:


  private:
    AssessmenttypeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(AssessmenttypeLoader)

#endif // ASSESSMENTTYPELOADER_H
