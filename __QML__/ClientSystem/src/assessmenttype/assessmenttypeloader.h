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
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    AssessmenttypeLoader(QObject *parent = 0);
    ~AssessmenttypeLoader();

    Q_INVOKABLE QString lastError() const;

    QString connectionName();
    bool setConnectionName( QString connectionName );

    bool started() const;

    Q_INVOKABLE bool load( const QString &filter = QString(), bool blockUI = false );

    int count() const;


  signals:
    void lastErrorChanged();
    void connectionNameChanged();
    void startedChanged();
    void newInfo( AssessmenttypeInfo *info );
    void countChanged();


  public slots:


  private:
    AssessmenttypeLoader_P *p;
    QEventLoop *loop;

  private slots:
    void threadStarted();
    void threadFinished();
    void receivedError( QString errorText );
};

QML_DECLARE_TYPE(AssessmenttypeLoader)

#endif // ASSESSMENTTYPELOADER_H
